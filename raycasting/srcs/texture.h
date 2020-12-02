#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdint.h>
#include "defs.h"
#include "upng.h"

typedef struct {
  upng_t* upngTexture;
  int width;
  int height;
  uint32_t* texture_buffer;
} texture_t;

texture_t wallTextures[NUM_TEXTURES];

void loadWallTextures();
void freeWallTextures();

#endif
