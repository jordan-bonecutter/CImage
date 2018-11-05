/* * * * * * * * * * * * * * * * * */
/* Editors.c * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#include "Editors.h"
#include <math.h>
#include <stdlib.h>
#define BLURMAX	10

pixel_t grayscale(pixel_t pixel, const args_t nargs)
{
	long val = (((long)pixel.R<<1) + pixel.R + (pixel.G<<2) + pixel.B)>>3;
	return (pixel_t){val, val, val};
}

static fpixel_t fpixelTransform(fpixel_t fpixel, const float matrix[3][3])
{
    // Memory for result
	fpixel_t result;

    // Perform multiplication
    result.E1 = matrix[0][0]*fpixel.E1 + matrix[0][1]*fpixel.E2 + matrix[0][2]*fpixel.E3;
    result.E2 = matrix[1][0]*fpixel.E1 + matrix[1][1]*fpixel.E2 + matrix[1][2]*fpixel.E3;
    result.E3 = matrix[2][0]*fpixel.E1 + matrix[2][1]*fpixel.E2 + matrix[2][2]*fpixel.E3;

	// Return result
	return result;
}

pixel_t huerotate(pixel_t pixel, const args_t angle)
{
	// Matrix to transform normalized
    // RGB color vector from the RGB
    // color space to the YIQ color space
	static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
                                               {0.596, -0.274, -0.321},
                                               {0.211, -0.523,  0.311}};

	// Matrix to transform normalized
    // YIQ color vector from the YIQ
    // color space to the RGB color space
    static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
                                               {1.000, -0.272, -0.647},
                                               {1.000, -1.107,  1.705}};

    const float cs = cos(FLOAT(angle)), ss = sin(FLOAT(angle));

    // Matrix to perform a hue
    // rotation on a normalized
    // YIQ color vector
    const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
                                                   {0.000, cs, -ss},
                                                   {0.000, ss, cs}};
	
	fpixel_t fpix = convertToFpixel(pixel);
	fpix = fpixelTransform(fpix, RGBtoYIQMatrix);
	fpix = fpixelTransform(fpix, XYPlaneVectorRotateMatrix);
	fpix = fpixelTransform(fpix, YIQtoRGBMatrix);

	return convertToPixel(fpix);
}

pixel_t saturate(pixel_t pixel, const args_t sat)
{
	// temporary flat pixel
	fpixel_t temp;

	// Get the grayscale pixel
	pixel_t gray = grayscale(pixel, NARGS);

	// Find the difference vector
	// taking the original vector
	// to the grayscale vector
	temp = (fpixel_t){(float)pixel.R - gray.R, (float)pixel.G - gray.G, (float)pixel.B - gray.B};

	// Move away/towards the 
	// grayscale vector
	temp = (fpixel_t){pixel.R - (temp.E1 * FLOAT(sat)), pixel.G - (temp.E2 * FLOAT(sat)), pixel.B - (temp.E3 * FLOAT(sat))};

	// Downscale the vector to
	// fit in 1 byte
	temp = (fpixel_t){temp.E1/255, temp.E2/255, temp.E3/255};

	// Return the transformed vector
	return convertToPixel(temp);
}

void boxblur(Image *image, int size)
{
	// Limit he size
	register long s = size > BLURMAX ? BLURMAX : size;

	// Calculate the kernel
	// size
	s <<= 1;
	s += 1;
	size = s;
	s *= s;

	// Alloc for the kernel
	float *blurKernel = malloc(sizeof(float) * s);

	// Init the kernel
	for(unsigned int n = 0; n < s; n++)
	{
		blurKernel[n] = (float)1/(s);
	}

	// Do the blur filter
	doKernelwise(image, blurKernel, size);

	// Free the kernel
	free(blurKernel);
}

void gaussianblur(Image *image, int size)
{
	register long s = size > BLURMAX ? BLURMAX : size;

	s <<= 1;
	s += 1;
	size = s;
	s *= s;

	float *blurKernel = malloc(sizeof(float) * s);
	double sum = 0, sigma = sqrt((float)size);;
	int x, y;

	for(unsigned int n = 0; n < s; n++)	
	{
		x = n%size;
		y = n/size;

		blurKernel[n] =  exp(-0.5 * (pow((x-((float)size/2)/sigma), 2.0) + pow((y-((float)size/2)/sigma),2.0))); 
		sum += blurKernel[n];
	}

	for(unsigned int n = 0; n < s; n++)
	{
		blurKernel[n] /= sum;
	}

	doKernelwise(image, blurKernel, size);

	free(blurKernel);

}
