#include "gd.h"
#include <stdio.h>
#include <math.h>
#define MAX_DELTA 25

int color_delta(int c1, int c2) {
  int delta;
  int r, g, b;
  r=gdTrueColorGetRed  (c1)-gdTrueColorGetRed  (c2); if (r<0) r=-r;
  g=gdTrueColorGetGreen(c1)-gdTrueColorGetGreen(c2); if (g<0) g=-g;
  b=gdTrueColorGetBlue (c1)-gdTrueColorGetBlue (c2); if (b<0) b=-b;
  delta=0;
  if (r>delta) delta=r;
  if (g>delta) delta=g;
  if (b>delta) delta=b;
  return delta;
}

int main(int argc, char **argv) {
  gdImagePtr im;
  int x, y, x_size, y_size, x_strip_l, x_strip_r, y_strip_t, y_strip_b;
  int f_x_l, f_x_r, f_y_t, f_y_b;
  int base_color;
  int point_color;
  int d;
  im = gdImageCreateFromFile(argv[1]);
  x_size=gdImageSX(im);
  y_size=gdImageSY(im);
  x_strip_l=0;
  x_strip_r=0;
  y_strip_t=0;
  y_strip_b=0;
  f_y_t=1;
  f_y_b=1;
  f_x_l=1;
  f_x_r=1;

  do {
    if (f_y_t) {
      x=x_strip_l;
      y=y_strip_t;
      base_color=gdImageTrueColorPixel(im, x, y);
      for (x=x_strip_l; x<x_size-x_strip_r; x++) {
        point_color=gdImageTrueColorPixel(im, x, y);
        d=color_delta(base_color, point_color);
        if (d>MAX_DELTA) {
          x=x_size;
          f_y_t=0;
        }
      }
      if (y_strip_t>(y_size>>1)) f_y_t=0;
      if (f_y_t) y_strip_t++;
    }

    if (f_y_b) {
      x=x_strip_l;
      y=y_size-y_strip_b-1;
      base_color=gdImageTrueColorPixel(im, x, y);
      for (x=x_strip_l; x<x_size-x_strip_r; x++) {
        point_color=gdImageTrueColorPixel(im, x, y);
        d=color_delta(base_color, point_color);
        if (d>MAX_DELTA) {
          x=x_size;
          f_y_b=0;
        }
      }
      if (y_strip_b>(y_size>>1)) f_y_b=0;
      if (f_y_b) y_strip_b++;
    }

    if (f_x_l) {
      x=x_strip_l;
      y=y_strip_t;
      base_color=gdImageTrueColorPixel(im, x, y);
      for (y=y_strip_t; y<y_size-y_strip_b; y++) {
        point_color=gdImageTrueColorPixel(im, x, y);
        d=color_delta(base_color, point_color);
        if (d>MAX_DELTA) {
          y=y_size;
          f_x_l=0;
        }
      }
      if (x_strip_l>(x_size>>1)) f_x_l=0;
      if (f_x_l) x_strip_l++;
    }

    if (f_x_r) {
      x=x_size-x_strip_r-1;
      y=y_strip_t;
      base_color=gdImageTrueColorPixel(im, x, y);
      for (y=y_strip_t; y<y_size-y_strip_b; y++) {
        point_color=gdImageTrueColorPixel(im, x, y);
        d=color_delta(base_color, point_color);
        if (d>MAX_DELTA) {
          y=y_size;
          f_x_r=0;
        }
      }
      if (x_strip_r>(x_size>>1)) f_x_r=0;
      if (f_x_r) x_strip_r++;
    }
  } while ((f_x_l)||(f_x_r)||(f_y_t)||(f_y_b));
  printf("%d,%d,%d,%d", x_strip_l, y_strip_t, x_size-x_strip_r, y_size-y_strip_b);
  gdImageDestroy(im);
}
