/* * * * * * * * * * * * * * * * * */
/* ImageEditor.h * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Image.h"

// For doing some image
// ops, it is nice to
// have float values
// rather than uchar
typedef struct
{
	float E1;
	float E2;
	float E3;
}fpixel_t;

// Convert pixel to fpixel
// (divides each component
// by 255)
fpixel_t convertToFpixel(pixel_t pixel);
// Convert fpixel to pixel
// (assumes RGB format and
// range from 0 -> 1)
pixel_t convertToPixel(fpixel_t fpixel);

// Args for imageEditors
typedef long args_t;
#define FLOAT(x) 	*((float 			*)(&x))
#define INT(x)		*((int   			*)(&x))
#define UINT(x)		*((unsigned 		*)(&x))
#define LONG(x)		*((long				*)(&x))
#define ULONG(x)	*((unsigned long 	*)(&x))
#define NARGS		((args_t){0})

#define ARGS(x)		*((args_t *)(&x))

// Just edits a single pixel
typedef pixel_t (*pixelwise_t)(pixel_t pixel, const args_t args);

void doPixelwise(Image *image, pixelwise_t editor, args_t args);
void doKernelwise(Image *image, float *kernel, int size);

#endif
