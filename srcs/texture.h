#ifndef TEXTURE_H
#define TEXTURE_H

#include "defs.h"
#include "config.h"
#include "../mlx/mlx.h"
#include <stdlib.h>

#define TEXTURE_WIDTH TILE_SIZE
#define TEXTURE_HEIGHT TILE_SIZE

void load_wall_texture(void);
void destroy_texture(void);

#endif
