/* * * * * * * * * * * * * * * * * */
/* ImageEditor.h * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Image.h"

// Args for imageEditors
typedef long args_t;
#define FLOAT(x) 	*((float 			*)(&x))
#define INT(x)		*((int   			*)(&x))
#define UINT(x)		*((unsigned 		*)(&x))
#define LONG(x)		*((long				*)(&x))
#define ULONG(x)	*((unsigned long 	*)(&x))
#define NARGS		((args_t){0l})

#define ARGS(x)		*((args_t *)(&x))

// Just edits a single pixel
typedef pixel_t (*pixelwise_t)(pixel_t pixel, const args_t args);

void doPixelwise(Image *image, pixelwise_t editor, args_t args);
void doKernelwise(Image *image, float *kernel, int size);

#endif
