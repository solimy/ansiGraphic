#include <unistd.h>
#include "ansiGraphic2.1.h"

int main(int ac, char**av) {
  ansigraphic_image_t* img = ansigraphic_readBmp(av[1]);
  ansigraphic_image_RGB_t* imgrgb = ansigraphic_readBmp_RGB(av[1]);

  while (42) {
    ansigraphic_imagePrint(img);
    usleep(1000000);
    ansigraphic_imagePrint_RGB(imgrgb);
    ansigraphic_image_RGB_reverse(imgrgb);
    usleep(1000000);
  }
  ansigraphic_deleteImage(img);
  ansigraphic_deleteImage_RGB(imgrgb);
  return 0;
}
