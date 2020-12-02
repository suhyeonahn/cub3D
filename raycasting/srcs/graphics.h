#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>
#include  <SDL2/SDL.h>
#include "defs.h"

bool	initializeWindow(void);
void	destroyWindow(void);
void	clearColorBuffer(color_t color);
void	renderColorBuffer(void);
void	drawPixel(int x, int y, color_t color);
void	drawRect(int w, int y, int width, int height, uint32_t color);
void	drawLine(int x0, int y0, int w1, int y1, uint32_t color);

#endif
