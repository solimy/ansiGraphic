#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ansiGraphic2.h" 

void ansigraphic_pixelSetColor(ansigraphic_image_t* image,
			       const ansigraphic_ivector2_t* xy,
			       const char* fgColor,
			       const char* bgColor) {
  char* pixel = image->pixels[xy->x + ((image->height-1-xy->y)*image->width)].pixel;
  pixel[7] = fgColor[0];
  pixel[8] = fgColor[1];
  pixel[9] = fgColor[2];
  pixel[16] = bgColor[0];
  pixel[17] = bgColor[1];
  pixel[18] = bgColor[2];
}

void ansigraphic_pixelSetColor_RGB(ansigraphic_image_RGB_t* image,
				   const ansigraphic_ivector2_t* xy,
				   const ansigraphic_color_RGB_t* fgColor,
				   const ansigraphic_color_RGB_t* bgColor) {
  char* pixel = image->pixels[xy->x + ((image->height-1-xy->y)*image->width)].pixel;
  pixel[7] = (*fgColor)[0][0];
  pixel[8] = (*fgColor)[0][1];
  pixel[9] = (*fgColor)[0][2];
  pixel[11] = (*fgColor)[1][0];
  pixel[12] = (*fgColor)[1][1];
  pixel[13] = (*fgColor)[1][2];
  pixel[15] = (*fgColor)[2][0];
  pixel[16] = (*fgColor)[2][1];
  pixel[17] = (*fgColor)[2][2];
  pixel[24] = (*bgColor)[0][0];
  pixel[25] = (*bgColor)[0][1];
  pixel[26] = (*bgColor)[0][2];
  pixel[28] = (*bgColor)[1][0];
  pixel[29] = (*bgColor)[1][1];
  pixel[30] = (*bgColor)[1][2];
  pixel[32] = (*bgColor)[2][0];
  pixel[33] = (*bgColor)[2][1];
  pixel[34] = (*bgColor)[2][2];
}

void ansigraphic_pixelGetColor_RGB(const ansigraphic_image_RGB_t* image,
				   const ansigraphic_ivector2_t* xy,
				   ansigraphic_color_RGB_t* fgColor,
				   ansigraphic_color_RGB_t* bgColor) {
  char* pixel = image->pixels[xy->x + ((image->height-1-xy->y)*image->width)].pixel;
  (*fgColor)[0][0] = pixel[7];
  (*fgColor)[0][1] = pixel[8];
  (*fgColor)[0][2] = pixel[9];
  (*fgColor)[1][0] = pixel[11];
  (*fgColor)[1][1] = pixel[12];
  (*fgColor)[1][2] = pixel[13];
  (*fgColor)[2][0] = pixel[15];
  (*fgColor)[2][1] = pixel[16];
  (*fgColor)[2][2] = pixel[17];
  (*bgColor)[0][0] = pixel[24];
  (*bgColor)[0][1] = pixel[25];
  (*bgColor)[0][2] = pixel[26];
  (*bgColor)[1][0] = pixel[28];
  (*bgColor)[1][1] = pixel[29];
  (*bgColor)[1][2] = pixel[30];
  (*bgColor)[2][0] = pixel[32];
  (*bgColor)[2][1] = pixel[33];
  (*bgColor)[2][2] = pixel[34];
}

void ansigraphic_pixelSetValue(ansigraphic_image_t* image,
			       const ansigraphic_ivector2_t* xy,
			       const char value) {
  char* pixel = image->pixels[xy->x + ((image->height-1-xy->y)*image->width)].pixel;
  pixel[20] = value;
}

void ansigraphic_pixelSetValue_RGB(ansigraphic_image_RGB_t* image,
				   const ansigraphic_ivector2_t* xy,
				   const char value) {
  char* pixel = image->pixels[xy->x + ((image->height-1-xy->y)*image->width)].pixel;
  pixel[36] = value;
}

void ansigraphic_imagePrint(ansigraphic_image_t* image) {
  write(1, "\033[u", 3);
  write(1, image->pixels, sizeof(ansigraphic_pixel_t)*image->width*image->height);
}

void ansigraphic_imagePrint_RGB(ansigraphic_image_RGB_t* image) {
  write(1, "\033[u", 3);
  write(1, image->pixels, sizeof(ansigraphic_pixel_RGB_t)*image->width*image->height);
}

void ansigraphic_imageClear(ansigraphic_image_t* image) {
  int32_t x, y, width=image->width, height=image->height;

  y = -1;
  while (++y < height) {
    x = -1;
    while (++x < width) {
      image->pixels[x + (y*width)].pixel[0] = '\033';
      image->pixels[x + (y*width)].pixel[1] = '[';
      image->pixels[x + (y*width)].pixel[2] = '3';
      image->pixels[x + (y*width)].pixel[3] = '8';
      image->pixels[x + (y*width)].pixel[4] = ';';
      image->pixels[x + (y*width)].pixel[5] = '5';
      image->pixels[x + (y*width)].pixel[6] = ';';
      image->pixels[x + (y*width)].pixel[7] = '0';
      image->pixels[x + (y*width)].pixel[8] = '0';
      image->pixels[x + (y*width)].pixel[9] = '0';
      image->pixels[x + (y*width)].pixel[10] = ';';
      image->pixels[x + (y*width)].pixel[11] = '4';
      image->pixels[x + (y*width)].pixel[12] = '8';
      image->pixels[x + (y*width)].pixel[13] = ';';
      image->pixels[x + (y*width)].pixel[14] = '5';
      image->pixels[x + (y*width)].pixel[15] = ';';
      image->pixels[x + (y*width)].pixel[16] = '0';
      image->pixels[x + (y*width)].pixel[17] = '0';
      image->pixels[x + (y*width)].pixel[18] = '0';
      image->pixels[x + (y*width)].pixel[19] = 'm';
      image->pixels[x + (y*width)].pixel[20] = ' ';
      if (x + 1 < width) {
	image->pixels[x + (y*width)].pixel[21] = 0;
      } else {
	image->pixels[x + (y*width)].pixel[21] = '\n';
      }
      image->pixels[x + (y*width)].pixel[22] = '\033';
      image->pixels[x + (y*width)].pixel[23] = '[';
      image->pixels[x + (y*width)].pixel[24] = '0';
      image->pixels[x + (y*width)].pixel[25] = 'm';
    }
  }
}

void ansigraphic_imageClear_RGB(ansigraphic_image_RGB_t* image) {
  int32_t x, y, width=image->width, height=image->height;

  y = -1;
  while (++y < height) {
    x = -1;
    while (++x < width) {
      image->pixels[x + (y*width)].pixel[0] = '\033';
      image->pixels[x + (y*width)].pixel[1] = '[';
      image->pixels[x + (y*width)].pixel[2] = '3';
      image->pixels[x + (y*width)].pixel[3] = '8';
      image->pixels[x + (y*width)].pixel[4] = ';';
      image->pixels[x + (y*width)].pixel[5] = '2';
      image->pixels[x + (y*width)].pixel[6] = ';';
      image->pixels[x + (y*width)].pixel[7] = '0';
      image->pixels[x + (y*width)].pixel[8] = '0';
      image->pixels[x + (y*width)].pixel[9] = '0';
      image->pixels[x + (y*width)].pixel[10] = ';';
      image->pixels[x + (y*width)].pixel[11] = '0';
      image->pixels[x + (y*width)].pixel[12] = '0';
      image->pixels[x + (y*width)].pixel[13] = '0';
      image->pixels[x + (y*width)].pixel[14] = ';';
      image->pixels[x + (y*width)].pixel[15] = '0';
      image->pixels[x + (y*width)].pixel[16] = '0';
      image->pixels[x + (y*width)].pixel[17] = '0';
      image->pixels[x + (y*width)].pixel[18] = ';';
      image->pixels[x + (y*width)].pixel[19] = '4';
      image->pixels[x + (y*width)].pixel[20] = '8';
      image->pixels[x + (y*width)].pixel[21] = ';';
      image->pixels[x + (y*width)].pixel[22] = '2';
      image->pixels[x + (y*width)].pixel[23] = ';';
      image->pixels[x + (y*width)].pixel[24] = '0';
      image->pixels[x + (y*width)].pixel[25] = '0';
      image->pixels[x + (y*width)].pixel[26] = '0';
      image->pixels[x + (y*width)].pixel[27] = ';';
      image->pixels[x + (y*width)].pixel[28] = '0';
      image->pixels[x + (y*width)].pixel[29] = '0';
      image->pixels[x + (y*width)].pixel[30] = '0';
      image->pixels[x + (y*width)].pixel[31] = ';';
      image->pixels[x + (y*width)].pixel[32] = '0';
      image->pixels[x + (y*width)].pixel[33] = '0';
      image->pixels[x + (y*width)].pixel[34] = '0';
      image->pixels[x + (y*width)].pixel[35] = 'm';
      image->pixels[x + (y*width)].pixel[36] = ' ';
      image->pixels[x + (y*width)].pixel[37] = '\033';
      image->pixels[x + (y*width)].pixel[38] = '[';
      image->pixels[x + (y*width)].pixel[39] = '0';
      image->pixels[x + (y*width)].pixel[40] = 'm';
      if (x + 1 < width) {
	image->pixels[x + (y*width)].pixel[41] = 0;
	image->pixels[x + (y*width)].pixel[42] = 0;
      } else {
	image->pixels[x + (y*width)].pixel[41] = '\r';
	image->pixels[x + (y*width)].pixel[42] = '\n';
      }
    }
  }
}

void ansigraphic_image_RGB_reverse(ansigraphic_image_RGB_t* image) {
  ansigraphic_color_RGB_t fg, bg;
  ansigraphic_ivector2_t xy;
  xy.y=0;
  while (xy.y < image->height) {
    xy.x = 0;
    while (xy.x < image->width) {
      ansigraphic_pixelGetColor_RGB(image, &xy, &fg, &bg);
      ansigraphic_color_RGB_reverse(&fg);
      ansigraphic_color_RGB_reverse(&bg);
      ansigraphic_pixelSetColor_RGB(image, &xy, &fg, &bg);
      ++xy.x;
    }
    ++xy.y;
  }
}

ansigraphic_image_t* ansigraphic_newImage(int32_t width,
					  int32_t height) {
  ansigraphic_image_t* image = (ansigraphic_image_t*)malloc(sizeof(ansigraphic_image_t));
  if (image == 0)
    return 0;
  else if ((image->pixels = (ansigraphic_pixel_t*)malloc(sizeof(ansigraphic_pixel_t)*width*height)) == 0) {
    free(image);
    return 0;
  }
  image->width = width;
  image->height = height;
  int32_t x, y;

  write(1, "\033[2J\033[0;0f\033[s", 13);
 
  y = -1;
  while (++y < height) {
    x = -1;
    while (++x < width) {
      image->pixels[x + (y*width)].pixel[0] = '\033';
      image->pixels[x + (y*width)].pixel[1] = '[';
      image->pixels[x + (y*width)].pixel[2] = '3';
      image->pixels[x + (y*width)].pixel[3] = '8';
      image->pixels[x + (y*width)].pixel[4] = ';';
      image->pixels[x + (y*width)].pixel[5] = '5';
      image->pixels[x + (y*width)].pixel[6] = ';';
      image->pixels[x + (y*width)].pixel[7] = '0';
      image->pixels[x + (y*width)].pixel[8] = '0';
      image->pixels[x + (y*width)].pixel[9] = '0';
      image->pixels[x + (y*width)].pixel[10] = ';';
      image->pixels[x + (y*width)].pixel[11] = '4';
      image->pixels[x + (y*width)].pixel[12] = '8';
      image->pixels[x + (y*width)].pixel[13] = ';';
      image->pixels[x + (y*width)].pixel[14] = '5';
      image->pixels[x + (y*width)].pixel[15] = ';';
      image->pixels[x + (y*width)].pixel[16] = '0';
      image->pixels[x + (y*width)].pixel[17] = '0';
      image->pixels[x + (y*width)].pixel[18] = '0';
      image->pixels[x + (y*width)].pixel[19] = 'm';
      image->pixels[x + (y*width)].pixel[20] = ' ';
      if (x + 1 < width) {
	image->pixels[x + (y*width)].pixel[21] = 0;
      } else {
	image->pixels[x + (y*width)].pixel[21] = '\n';
      }
      image->pixels[x + (y*width)].pixel[22] = '\033';
      image->pixels[x + (y*width)].pixel[23] = '[';
      image->pixels[x + (y*width)].pixel[24] = '0';
      image->pixels[x + (y*width)].pixel[25] = 'm';
    }
  }
  return image;
}

ansigraphic_image_RGB_t* ansigraphic_newImage_RGB(int32_t width,
						  int32_t height) {
  ansigraphic_image_RGB_t* image = (ansigraphic_image_RGB_t*)malloc(sizeof(ansigraphic_image_RGB_t));
  if (image == 0)
    return 0;
  else if ((image->pixels = (ansigraphic_pixel_RGB_t*)malloc(sizeof(ansigraphic_pixel_RGB_t)*width*height)) == 0) {
    free(image);
    return 0;
  }
  image->width = width;
  image->height = height;
  int32_t x, y;

  write(1, "\033[2J\033[0;0f\033[s", 13);
  
  y = -1;
  while (++y < height) {
    x = -1;
    while (++x < width) {
      image->pixels[x + (y*width)].pixel[0] = '\033';
      image->pixels[x + (y*width)].pixel[1] = '[';
      image->pixels[x + (y*width)].pixel[2] = '3';
      image->pixels[x + (y*width)].pixel[3] = '8';
      image->pixels[x + (y*width)].pixel[4] = ';';
      image->pixels[x + (y*width)].pixel[5] = '2';
      image->pixels[x + (y*width)].pixel[6] = ';';
      image->pixels[x + (y*width)].pixel[7] = '0';
      image->pixels[x + (y*width)].pixel[8] = '0';
      image->pixels[x + (y*width)].pixel[9] = '0';
      image->pixels[x + (y*width)].pixel[10] = ';';
      image->pixels[x + (y*width)].pixel[11] = '0';
      image->pixels[x + (y*width)].pixel[12] = '0';
      image->pixels[x + (y*width)].pixel[13] = '0';
      image->pixels[x + (y*width)].pixel[14] = ';';
      image->pixels[x + (y*width)].pixel[15] = '0';
      image->pixels[x + (y*width)].pixel[16] = '0';
      image->pixels[x + (y*width)].pixel[17] = '0';
      image->pixels[x + (y*width)].pixel[18] = ';';
      image->pixels[x + (y*width)].pixel[19] = '4';
      image->pixels[x + (y*width)].pixel[20] = '8';
      image->pixels[x + (y*width)].pixel[21] = ';';
      image->pixels[x + (y*width)].pixel[22] = '2';
      image->pixels[x + (y*width)].pixel[23] = ';';
      image->pixels[x + (y*width)].pixel[24] = '0';
      image->pixels[x + (y*width)].pixel[25] = '0';
      image->pixels[x + (y*width)].pixel[26] = '0';
      image->pixels[x + (y*width)].pixel[27] = ';';
      image->pixels[x + (y*width)].pixel[28] = '0';
      image->pixels[x + (y*width)].pixel[29] = '0';
      image->pixels[x + (y*width)].pixel[30] = '0';
      image->pixels[x + (y*width)].pixel[31] = ';';
      image->pixels[x + (y*width)].pixel[32] = '0';
      image->pixels[x + (y*width)].pixel[33] = '0';
      image->pixels[x + (y*width)].pixel[34] = '0';
      image->pixels[x + (y*width)].pixel[35] = 'm';
      image->pixels[x + (y*width)].pixel[36] = ' ';
      image->pixels[x + (y*width)].pixel[37] = '\033';
      image->pixels[x + (y*width)].pixel[38] = '[';
      image->pixels[x + (y*width)].pixel[39] = '0';
      image->pixels[x + (y*width)].pixel[40] = 'm';
      if (x + 1 < width) {
	image->pixels[x + (y*width)].pixel[41] = 0;
	image->pixels[x + (y*width)].pixel[42] = 0;
      } else {
	image->pixels[x + (y*width)].pixel[41] = '\r';
	image->pixels[x + (y*width)].pixel[42] = '\n';
      }
    }
  }
  return image;
}

void ansigraphic_color_RGB_set(ansigraphic_color_RGB_t* color,
			       int red,
			       int green,
			       int blue) {
  char tmp[4];

  if (red >= 0 && red <= 255) {
    snprintf(tmp, 4, "%03d", red);
    memcpy((*color)[0], tmp, 3);
  }
  if (green >= 0 && green <= 255) {
    snprintf(tmp, 4, "%03d", green);
    memcpy((*color)[1], tmp, 3);
  }
  if (blue >= 0 && blue <= 255) {
    snprintf(tmp, 4, "%03d", blue);
    memcpy((*color)[2], tmp, 3);
  }
}

void ansigraphic_color_RGB_reverse(ansigraphic_color_RGB_t* color) {
  char tmp[4]; tmp[3]=0;
  int r, g, b;
  tmp[0] = (*color)[0][0];
  tmp[1] = (*color)[0][1];
  tmp[2] = (*color)[0][2];
  r = 255-atoi(tmp);
  tmp[0] = (*color)[1][0];
  tmp[1] = (*color)[1][1];
  tmp[2] = (*color)[1][2];
  g = 255-atoi(tmp);
  tmp[0] = (*color)[2][0];
  tmp[1] = (*color)[2][1];
  tmp[2] = (*color)[2][2];
  b = 255-atoi(tmp);
  ansigraphic_color_RGB_set(color, r, g, b);
}

void ansigraphic_drawLine(ansigraphic_image_t* image,
			  const ansigraphic_dvector2_t* start,
			  const ansigraphic_dvector2_t* end,
			  char value,
			  const char* fgColor,
			  const char* bgColor) {
  double delx=start->x-end->x, dely=start->y-end->y;
  double sx=(delx < 0 ? -1 : 1), sy=(dely < 0 ? -1 : 1);
  double disx=(delx < 0 ? -delx : delx), disy=(dely < 0 ? -dely : dely);
  double xa=(start->x), ya=(start->y);
  ansigraphic_ivector2_t xy;
  
  if (disx > disy) {
    double dd=(disx / disy);
    while (disx > 0 || disy > 0) {
      xy.x = (int)xa;
      xy.y = (int)ya;
      ansigraphic_pixelSetColor(image, &xy, fgColor, bgColor);
      xa -= sx*1;
      disx -= 1;
      ya -= sy*(1/dd);
      disy -= 1/dd;
    }
  } else {
    double dd=(disy / disx);
    while (disx > 0 || disy > 0) {
      xy.x = (int)xa;
      xy.y = (int)ya;
      ansigraphic_pixelSetColor(image, &xy, fgColor, bgColor);
      xa -= sx*(1/dd);
      disx -= 1/dd;
      ya -= sy*1;
      disy -= 1;
    }
  }
}

void ansigraphic_drawLine_RGB(ansigraphic_image_RGB_t* image,
			      const ansigraphic_dvector2_t* start,
			      const ansigraphic_dvector2_t* end,
			      char value,
			      const ansigraphic_color_RGB_t* fgColor,
			      const ansigraphic_color_RGB_t* bgColor) {
  double delx=start->x-end->x, dely=start->y-end->y;
  double sx=(delx < 0 ? -1 : 1), sy=(dely < 0 ? -1 : 1);
  double disx=(delx < 0 ? -delx : delx), disy=(dely < 0 ? -dely : dely);
  double xa=(start->x), ya=(start->y);
  ansigraphic_ivector2_t xy;

  if (disx > disy) {
    double dd=(disx / disy);
    while (disx > 0 || disy > 0) {
      xy.x = (int)xa;
      xy.y = (int)ya;
      ansigraphic_pixelSetColor_RGB(image, &xy, fgColor, bgColor);
      xa -= sx*1;
      disx -= 1;
      ya -= sy*(1/dd);
      disy -= 1/dd;
    }
  } else {
    double dd=(disy / disx);
    while (disx > 0 || disy > 0) {
      xy.x = (int)xa;
      xy.y = (int)ya;
      ansigraphic_pixelSetColor_RGB(image, &xy, fgColor, bgColor);
      xa -= sx*(1/dd);
      disx -= 1/dd;
      ya -= sy*1;
      disy -= 1;
    }
  }
}

ansigraphic_image_t* ansigraphic_readBmp(const char* fileName) {
  int i;
  FILE* f = fopen(fileName, "rb");
  unsigned char info[54];
  fread(info, sizeof(unsigned char), 54, f);
  int width = *(int*)&info[18];
  int height = *(int*)&info[22];
  int row_padded = (width*3 + 3) & (~3);
  unsigned char* data = malloc(sizeof(unsigned char)*row_padded);
  ansigraphic_image_t* img = ansigraphic_newImage(width, height);
  ansigraphic_ivector2_t pixelPosition;
  unsigned char tmp;

  int li, lj;
  li = 0;
  while(li < height)
    {
      lj = 0;
      fread(data, sizeof(unsigned char), row_padded, f);
      while(lj < width*3)
	{
	  tmp = data[lj];
	  data[lj] = data[lj+2];
	  data[lj+2] = tmp;

	  pixelPosition.x = lj/3;
	  pixelPosition.y = li;
	  int moy=((data[lj]+data[lj+1]+data[lj+2])/3);
	  char val=(moy < 50 ? '|' : (moy < 100 ? '!' : (moy < 150 ? ':' : (moy < 200 ? '.' : (' ')))));
	  ansigraphic_pixelSetColor(img, &pixelPosition, "015", "000");
	  ansigraphic_pixelSetValue(img, &pixelPosition, val);
	  lj+=3;
	}
      ++li;
    }
  fclose(f);
  free(data);
  return img;
}

ansigraphic_image_RGB_t* ansigraphic_readBmp_RGB(const char* fileName) {
  int i;
  FILE* f = fopen(fileName, "rb");
  unsigned char info[54];
  fread(info, sizeof(unsigned char), 54, f);
  int width = *(int*)&info[18];
  int height = *(int*)&info[22];
  int row_padded = (width*3 + 3) & (~3);
  unsigned char* data = malloc(sizeof(unsigned char)*row_padded);
  ansigraphic_image_RGB_t* img = ansigraphic_newImage_RGB(width, height);
  ansigraphic_ivector2_t pixelPosition;
  unsigned char tmp;
  ansigraphic_color_RGB_t color;

  int li, lj;
  li = 0;
  while(li < height)
    {
      lj = 0;
      fread(data, sizeof(unsigned char), row_padded, f);
      while(lj < width*3)
	{
	  tmp = data[lj];
	  data[lj] = data[lj+2];
	  data[lj+2] = tmp;

	  ansigraphic_color_RGB_set(&color, data[lj], data[lj+1], data[lj+2]);
	  pixelPosition.x = lj/3;
	  pixelPosition.y = li;
	  ansigraphic_pixelSetColor_RGB(img, &pixelPosition, &color, &color);
	  lj+=3;
	}
      ++li;
    }
  fclose(f);
  free(data);
  return img;
}

void ansigraphic_spritePrint(ansigraphic_image_t* dest, const ansigraphic_sprite_t* src) {
  int x, xlim;
  int y, ylim;
  char *pixelDest, *pixelSrc;

  y = 0;
  while (src->xy.y + y < dest->height && y < src->image->height) {
    x = 0;
    while (src->xy.x + x < dest->width && x < src->image->width) {
      pixelDest=dest->pixels[(src->xy.x + x) + ((src->xy.y + y)*dest->width)].pixel;
      pixelSrc=src->image->pixels[x + (y*src->image->width)].pixel;
      pixelDest[7] = pixelSrc[7];
      pixelDest[8] = pixelSrc[8];
      pixelDest[9] = pixelSrc[9];
      pixelDest[16] = pixelSrc[16];
      pixelDest[17] = pixelSrc[17];
      pixelDest[18] = pixelSrc[18];
      pixelDest[20] = pixelSrc[20];
      ++x;
    }
    ++y;
  }
}

void ansigraphic_spritePrint_RGB(ansigraphic_image_RGB_t* dest, const ansigraphic_sprite_RGB_t* src) {
  int x, xlim;
  int y, ylim;
  char *pixelDest, *pixelSrc;

  y = 0;
  while (src->xy.y + y < dest->height && y < src->image->height) {
    x = 0;
    while (src->xy.x + x < dest->width && x < src->image->width) {
      pixelDest=dest->pixels[(src->xy.x + x) + ((src->xy.y + y)*dest->width)].pixel;
      pixelSrc=src->image->pixels[x + (y*src->image->width)].pixel;
      pixelDest[7] = pixelSrc[7];
      pixelDest[8] = pixelSrc[8];
      pixelDest[9] = pixelSrc[9];
      pixelDest[11] = pixelSrc[11];
      pixelDest[12] = pixelSrc[12];
      pixelDest[13] = pixelSrc[13];
      pixelDest[15] = pixelSrc[15];
      pixelDest[16] = pixelSrc[16];
      pixelDest[17] = pixelSrc[17];
      pixelDest[24] = pixelSrc[24];
      pixelDest[25] = pixelSrc[25];
      pixelDest[26] = pixelSrc[26];
      pixelDest[28] = pixelSrc[28];
      pixelDest[29] = pixelSrc[29];
      pixelDest[30] = pixelSrc[30];
      pixelDest[32] = pixelSrc[32];
      pixelDest[33] = pixelSrc[33];
      pixelDest[34] = pixelSrc[34];
      pixelDest[36] = pixelSrc[36];
      ++x;
    }
    ++y;
  }
}