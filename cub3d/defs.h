#ifndef DEFS_H
#define DEFS_H

#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <mlx.h>
#include <X11/X.h>
#include <unistd.h>
#include "config.h"

#define TILE_SIZE 64

#define MINIMAP_SCALE_FACTOR 0.2

#define PI 3.14159265
#define TWO_PI 6.28318530

#define WINDOW_WIDTH config.width
#define WINDOW_HEIGHT config.height

#define FOV_ANGLE (60 * (PI / 180))

//#define NUM_RAYS 1920

#define DIST_PROJ_PLANE ((config.width / 2) / tan(FOV_ANGLE / 2))

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define KEY_UP 126 
#define KEY_DOWN 125
#define KEY_RIGHT 124
#define KEY_LEFT 123

void *mlx_ptr;
void *win_ptr;

//typedef uint32_t color_t;

#endif
