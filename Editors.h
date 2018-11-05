/* * * * * * * * * * * * * * * * * */
/* Editors.h * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef EDITORS_H
#define EDITORS_H

#include "Image.h"
#include "ImageEditor.h"

pixel_t grayscale(pixel_t pixel, const args_t nargs);
pixel_t huerotate(pixel_t pixel, const args_t angle);
pixel_t saturate(pixel_t pixel, const args_t sat);

void boxblur(Image *image, int size);
void gaussianblur(Image *image, int size);

#endif
