#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defs.h"
#include "../mlx/mlx.h"
#include <X11/X.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

//void	destroyWindow(void);
void	draw_rect(int x, int y, int width, int height, uint32_t color);
void	draw_line(int x0, int y0, int w1, int y1, uint32_t color);

#endif
