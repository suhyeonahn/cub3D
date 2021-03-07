#ifndef DEFS_H
#define DEFS_H

#include <math.h>

#define TILE_SIZE 64

#define PI 3.14159265
#define TWO_PI 6.28318530

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 960

#define FOV_ANGLE (60 * (PI / 180))

//#define NUM_RAYS 1920

#define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define KEY_UP 126 
#define KEY_DOWN 125
#define KEY_RIGHT 124
#define KEY_LEFT 123

#define TYPE_R				9
#define TYPE_NO				1
#define TYPE_SO				2
#define TYPE_WE				3
#define TYPE_EA				4
#define TYPE_S				5
#define TYPE_F				6
#define TYPE_C				7
#define TYPE_MAP			8

#define NUM_TEXTURES 4

extern void *mlx_ptr;
extern void *win_ptr;

//typedef uint32_t color_t;
#endif
