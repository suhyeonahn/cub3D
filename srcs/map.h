#ifndef MAP_H
#define MAP_H

#include "defs.h"
#include "config.h"
#include "sprite.h"
#include "utils.h"
#include "graphics.h"
#include <stdbool.h>
#include <stdbool.h>

#define VALID_MAP_CHARACTERS " 01234NSEW"
#define DIRECTIONS "NSEW"
#define MINIMAP_SCALE_FACTOR 0.15

int count_check_columns(char const *line);
int check_top_bottom_borders(void);
int check_left_right_borders(void);
int check_map_valid(void);
int	copy_map(void);
int parse_map(void);
bool map_has_wall_at(float x, float y);
bool map_has_sprite_at(t_sprite **sprite, float x, float y);
bool is_inside_map(float x, float y);
int	get_map_at(int i, int j);
void render_map(void);

#endif
