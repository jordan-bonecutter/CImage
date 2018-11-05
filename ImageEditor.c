/* * * * * * * * * * * * * * * * * */
/* ImageEditor.c * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#include "ImageEditor.h"

fpixel_t convertToFpixel(pixel_t pixel)
{
	return (fpixel_t){((float)pixel.R)/255, ((float)pixel.G)/255, ((float)pixel.B)/255};
}

pixel_t convertToPixel(fpixel_t fpixel)
{
	fpixel.E1 = fpixel.E1 < 0 ? 0 : fpixel.E1;
	fpixel.E1 = fpixel.E1 > 1 ? 1 : fpixel.E1;
	fpixel.E2 = fpixel.E2 < 0 ? 0 : fpixel.E2;
	fpixel.E2 = fpixel.E2 > 1 ? 1 : fpixel.E2;
	fpixel.E3 = fpixel.E3 < 0 ? 0 : fpixel.E3;
	fpixel.E3 = fpixel.E3 > 1 ? 1 : fpixel.E3;

	return (pixel_t){fpixel.E1 * 255, fpixel.E2 * 255, fpixel.E3 * 255};
}

#ifndef WINDOWS
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define THREADNUM	4	
struct threadArgs
{
	Image *image;
	pixelwise_t editor;
	args_t args;
	unsigned int xstart;
	unsigned int ystart;
	unsigned int xstop;
	unsigned int ystop;
	unsigned int n;
};

#define EARG(x) (*((struct threadArgs *)(x)))

static void *doSection(void *vargp)
{
	printf("Hello from thread %d!\n", EARG(vargp).n);
	// Does a section of the 
	// image for multithreading
	for(unsigned int i = EARG(vargp).xstart; i <= EARG(vargp).xstop; i++)
	{
		for(unsigned int j = EARG(vargp).ystart; j < EARG(vargp).ystop; j++)
		{
			setPixel(EARG(vargp).image, i, j, EARG(vargp).editor(getPixel(EARG(vargp).image, i, j), EARG(vargp).args));
		}
	}

	printf("Goodbye from thread %d!\n", EARG(vargp).n);

	return NULL;
}

void doPixelwise(Image *image, pixelwise_t editor, args_t args)
{
	// Create threads to be
	// released on the image
	pthread_t threads[THREADNUM];
	struct threadArgs threadArgs[THREADNUM];
	for(unsigned int n = 0; n < THREADNUM; n++)
	{
		threadArgs[n] = (struct threadArgs){image, editor, args, (n)*imageWidth(image)/THREADNUM, 
			0, ((n+1)*imageWidth(image)/THREADNUM) - 1, imageHeight(image) - 1, n};
		pthread_create(&(threads[n]), NULL, doSection, &threadArgs[n]);
	}

	// Join the threads!
	for(unsigned int n = 0; n < THREADNUM; n++)
	{
		pthread_join(threads[n], NULL);
	}
}

#endif

#ifdef WINDOWS
void doPixelwise(Image *image, pixelwise_t editor, args_t args)
{
	const unsigned int WIDTH = imageWidth(image);
	const unsigned int HEIGHT = imageHeight(image);
	for(unsigned int i = 0; i < WIDTH; i++)
	{
		for(unsigned int j = 0; j < HEIGHT; j++)
		{
			setPixel(image, i, j, editor(getPixel(image, i, j), args));
		}
	}
}

#endif

void doKernelwise(Image *image, float *kernel, int size)
{
	const unsigned int WIDTH = imageWidth(image);
	const unsigned int HEIGHT = imageHeight(image);
	float sumR, sumG, sumB;
	pixel_t temp;

	Image *imtemp = newImage(WIDTH, HEIGHT);

	for(unsigned int i = (size>>1); i < WIDTH - (size>>1); i++)
	{
		for(unsigned int j = (size>>1); j < HEIGHT - (size>>1); j++)
		{
			sumR = 0;
			sumG = 0;
			sumB = 0;

			// Kernel Convolution
			for(int n = -size/2; n <= size/2; n++)
			{
				for(int m = -size/2; m <= size/2; m++)
				{
					temp = getPixel(image, i + n, j + m);
					
					sumR += kernel[(n + size/2) + (m + size/2) * size] * temp.R;
					sumG += kernel[(n + size/2) + (m + size/2) * size] * temp.G;
					sumB += kernel[(n + size/2) + (m + size/2) * size] * temp.B;
				}
			}

			sumR = sumR < 0 ? 0 : sumR;
			sumR = sumR > 255 ? 255 : sumR;
			sumG = sumG < 0 ? 0 : sumG;
			sumG = sumG > 255 ? 255 : sumG;
			sumB = sumB < 0 ? 0 : sumB;
			sumB = sumB > 255 ? 255 : sumB;

			setPixel(imtemp, i, j, (pixel_t){(unsigned char)sumR, (unsigned char)sumG, (unsigned char)sumB});
		}
	}

	for(unsigned int i = 0; i < WIDTH; i++)
	{
		for(unsigned int j = 0; j < HEIGHT; j++)
		{
			setPixel(image, i, j, getPixel(imtemp, i, j));
		}
	}

	releaseImage(imtemp);
}
