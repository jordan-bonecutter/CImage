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

// Fmage declaration
typedef void Fmage;

Fmage *newFmage(unsigned int width, unsigned int height);
Fmage *newFmageFromFile(char *fname);
Fmage *copyFmage(Fmage *fmage);
	// Release
void releaseFmage(Fmage *fmage);
	// Accessors
pixel_t getPixel(const Fmage *fmage, unsigned int x, unsigned int y);

unsigned char getPixelR(const Fmage *fmage, unsigned int x, unsigned int y);
unsigned char getPixelG(const Fmage *fmage, unsigned int x, unsigned int y);
unsigned char getPixelB(const Fmage *fmage, unsigned int x, unsigned int y);
void setPixelR(Fmage *fmage, unsigned int x, unsigned int y, unsigned char set);
void setPixelG(Fmage *fmage, unsigned int x, unsigned int y, unsigned char set);
void setPixelB(Fmage *fmage, unsigned int x, unsigned int y, unsigned char set);

unsigned int fmageWidth(const Fmage *fmage);
unsigned int fmageHeight(const Fmage *fmage);
	// Mutors
void setPixel(Fmage *fmage, unsigned int x, unsigned int y, pixel_t pixel);
	// Misc
int saveFmage(const Fmage *fmage, char *fname);

#endif
