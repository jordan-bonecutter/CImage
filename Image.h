/* * * * * * * * * * * * * * * * * */
/* Image.h * * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef IMAGE_H
#define IMAGE_H

// Pixel
typedef struct
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}pixel_t;

// Image declaration
typedef void Image;

// Image functions
	// Alloc (black canvas)
Image *newImage(unsigned int width, unsigned int height);
Image *newImageFromFile(char *fname);
Image *copyImage(Image *image);
	// Release
void releaseImage(Image *image);
	// Accessors
pixel_t getPixel(const Image *image, unsigned int x, unsigned int y);

unsigned char getPixelR(const Image *image, unsigned int x, unsigned int y);
unsigned char getPixelG(const Image *image, unsigned int x, unsigned int y);
unsigned char getPixelB(const Image *image, unsigned int x, unsigned int y);
void setPixelR(Image *image, unsigned int x, unsigned int y, unsigned char set);
void setPixelG(Image *image, unsigned int x, unsigned int y, unsigned char set);
void setPixelB(Image *image, unsigned int x, unsigned int y, unsigned char set);

unsigned int imageWidth(const Image *image);
unsigned int imageHeight(const Image *image);
	// Mutors
void setPixel(Image *image, unsigned int x, unsigned int y, pixel_t pixel);
	// Misc
int saveImage(const Image *image, char *fname);

#endif
