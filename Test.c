/* * * * * * * * * * * * * * * * * */
/* Test.c  * * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#include "Image.h"
#include "ImageEditor.h"
#include "Editors.h"

#ifdef TIMETRIALS
#include <time.h>
#include <stdio.h>
#endif

int main()
{
#ifdef TIMETRIALS
	clock_t start = clock();
#endif

	Image *cx = newImageFromFile("HSSOE");

	doPixelwise(cx, grayscale, NARGS);
	Image *cy = copyImage(cx);
	float edgeY[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
	float edgeX[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	doKernelwise(cx, edgeX, 3);
	doKernelwise(cy, edgeY, 3);

	saveImage(cx, "sobel_x");
	saveImage(cy, "sobel_y");

	releaseImage(cx);
	releaseImage(cy);

#ifdef TIMETRIALS
	clock_t end = clock();
	printf("%ld ticks\n", end - start);
#endif

	return 0;
}
