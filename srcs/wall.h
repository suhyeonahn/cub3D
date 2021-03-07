#ifndef WALL_H
#define WALL_H

#include "defs.h"
#include "config.h"
#include "ray.h"
#include "texture.h"
#include "../mlx/mlx.h"
#include <X11/X.h>

#define TEXTURE_WIDTH TILE_SIZE
#define TEXTURE_HEIGHT TILE_SIZE

void render_wall_projection(void);

#endif
