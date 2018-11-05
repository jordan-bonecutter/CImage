/* * * * * * * * * * * * * * * * * */
/* Image.c * * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#include "Image.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define unravel(x) ((struct img *)x)

#define BSIZE		20
#define PIXELMAX	"255\n"

struct img
{
	unsigned int width;
	unsigned int height;
	pixel_t *pixels;
};

Image *newImage(unsigned int width, unsigned int height)
{
	// Alloc
	struct img *i = malloc(sizeof(struct img));

	// Init
	i->width = width;
	i->height = height;
	i->pixels = calloc(sizeof(pixel_t), width *height);

	// Return
	return i;
}

Image *copyImage(Image *image)
{
	// Alloc
	struct img *copy = newImage(unravel(image)->width, unravel(image)->height);

	// Init
	for(unsigned int i = 0; i < unravel(image)->width, i++)
	{
		for(unsigned int j = 0; j < unravel(image)->height; j++)
		{
			// Copy each pixel
			copy->pixels[i + j * unravel(image)->width] = unravel(image)->pixels[i + j * unravel(image)->width];
		}
	}

	// Return
	return copy;
}

void releaseImage(Image *image)
{
	// Assert
	assert(image);
	assert(unravel(image)->pixels);

	// Free pixels
	free(unravel(image)->pixels);

	// Erase memory
	unravel(image)->width = 0;
	unravel(image)->height = 0;

	// Free image struct
	free(image);
}

pixel_t getPixel(const Image *image, unsigned int x, unsigned int y)
{
	// Assert
	assert(image);
	assert(unravel(image)->pixels);

	// Return
	return unravel(image)->pixels[x + y * unravel(image)->width];
}

unsigned int imageWidth(const Image *image)
{
	// Assert
	assert(image);
	assert(unravel(image)->pixels);

	return unravel(image)->width;
}

unsigned int imageHeight(const Image *image)
{
	// Assert
	assert(image);
	assert(unravel(image)->pixels);

	return unravel(image)->height;
}

void setPixel(Image *image, unsigned int x, unsigned int y, pixel_t pixel)
{
	// Assert
	assert(image);
	assert(unravel(image)->pixels);

	// Set
	unravel(image)->pixels[x + y * unravel(image)->width] = pixel;
}

int saveImage(const Image *image, char *fname)
{
	char *s, *t;
	if(!strstr(fname, ".ppm"))
	{
		s = malloc(sizeof(char) * (strlen(fname) + 5));
		memcpy(s, fname, strlen(fname));
		t = s;
		s += strlen(fname);
		*s++ = '.';
		*s++ = 'p';
		*s++ = 'p';
		*s++ = 'm';
		*s = 0;
		s = t;
	}
	else
	{
		s = fname;
	}

	// Decalre buff on stack
	char buff[BSIZE];
	memset(buff, 0, BSIZE);

	// Open the file!
	FILE *fp = fopen(s, "w");
	
	// If s was alloc'd
	if(s != fname)
	{
		free(s);
	}

	// If the file couldn't be opened
	if(!fp)
	{
#ifndef NDEBUG
		printf("Invalid file name!\n");
#endif
		return -1;
	}

	// Magic string for ppm
	fputs("P6\n", fp);

	// Put image size
	sprintf(buff, "%d %d\n", unravel(image)->width, unravel(image)->height);
	fputs(buff, fp);
	memset(buff, 0, BSIZE);

	// Max pixel is 255
	fputs(PIXELMAX, fp);

	// Loop!
	pixel_t curr;
	for(unsigned int i = 0; i < unravel(image)->height; i++)
	{
		for(unsigned int j = 0; j < unravel(image)->width; j++)
		{
			curr = getPixel(image, j, i);
			fputc((char)curr.R, fp);
			fputc((char)curr.G, fp);
			fputc((char)curr.B, fp);
		}
	}

	fclose(fp);

	return 0;
}

Image *newImageFromFile(char *fname)
{
	// Set filetype
	struct img *ret = NULL;
	char *s, *t;
	long width, height, temp;
	pixel_t pixel;

	if(!strstr(fname, ".ppm"))
	{
		s = malloc(sizeof(char) * (strlen(fname) + 5));
		memcpy(s, fname, strlen(fname));
		t = s;
		s += strlen(fname);
		*s++ = '.';
		*s++ = 'p';
		*s++ = 'p';
		*s++ = 'm';
		*s = 0;
		s = t;
	}
	else
	{
		s = fname;
	}

	// Open the file!
	FILE *fp = fopen(s, "r");
	
	if(s != fname)
	{
		free(s);
	}

	// If unseccuesful
	if(!fp)
	{
#ifndef NDEBUG
		printf("Invalid filename!\n");
#endif
		return NULL;
	}
	
	// Make sure the magic
	// string is P6 (color)
	if(!(fgetc(fp) == 'P' && fgetc(fp) == '6' && fgetc(fp) == '\n'))
	{
#ifndef NDEBUG
		printf("Invalid color gamut type!\n");
#endif
		fclose(fp);
		return NULL;
	}
	
	// Get width
	fscanf(fp, "%ld", &width);
	fscanf(fp, "%ld", &height);
	if(width <= 0 || height <= 0)
	{
#ifndef NDEBUG
		printf("File specifies image with negative dimensions (%ld x %ld)...\n", width, height);
#endif
		fclose(fp);
		return NULL;
	}

	// Check if maxval is correct
	fscanf(fp, "%ld", &temp);
	if(temp != 255)
	{
#ifndef NDEBUG
		printf("Unsupported image type (MAXVALUE of each pixel must be 255, file specified %ld\n)", temp);
#endif
		fclose(fp);
		return NULL;
	}

	// Check for endline
	if(fgetc(fp) != '\n')
	{
#ifndef NDEBUG
		printf("Error found in file, file may be corrupted/unsupported\n");
#endif
		fclose(fp);
		return NULL;
	}

	ret = newImage(width, height);

	for(unsigned int i = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			pixel.R = (unsigned char)fgetc(fp);
			pixel.G = (unsigned char)fgetc(fp);
			pixel.B = (unsigned char)fgetc(fp);

			setPixel(ret, j, i, pixel);
		}
	}

	fclose(fp);
	return ret;
}
