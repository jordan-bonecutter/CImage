# CImage
An Image library I've been working on in my spare time

To allocate a new Image object do:
  ```
  Image *new = newImage(width, height);
  ```
  All pixels are black by default

To set a pixel in the image do:
  ```
  setPixel(new, width, height, (pixel_t){0, 0, 0xFF});
  ```
  OR
  
  ```
  pixel_t p;
  p.R = 0;
  p.G = 0;
  p.B = 0xFF;
  setPixel(new, width, height, p);
  ```
To define a new pixel by pixel operator do:
  ```
  SomeFilter.h:
  pixel_t someFilter(pixel_t p, const args_t args);
  
  SomeFilter.c:
  pixel_t someFilter(pixel_t p, const args_t args)
  {
    pixel_t ret;
    float args = FLOAT(args);
    // Do operation on pixel
  
    return ret;
  }
  ```
  To use args_t:
    1. Decide which type you want to pass (you can't pass more than one type)
    2. In your function body, cast your args as follows:
    ```
      a. float         => FLOAT(x)
      b. int           => INT  (x)
      c. unsigned      => UINT (x)
      d. unsigned long => ULONG(x)
      e. no arguments  => NARGS
      ```
    3. When passing the variable simply use:
      ARGS(x)

To use a pixel by pixel operator do:
  doPixelwise(image, someFilter, ARGS(somevalue));
  
To use an image kernel (for example the sobel x kernel) do:
  ```
  float sobel_x[3][3] = {-1, 0, 1, 
                         -2, 0, 2, 
                         -1, 0, 1};
  doKernelwise(image, sobel_x, 3);
  ```
  
To save an image to a ppm file do:
  ```saveImage(image, "filename");```

To load an image from a file do:
  ```Image *new = newImageFromFile("filename");```
  
Finally to release the heap space for the image do:
  ```releaseImage(image);```
    
