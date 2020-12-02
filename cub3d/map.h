#ifndef MAP_H
#define MAP_H

#include "defs.h"
#include "config.h"
#include "utils.h"
#include "graphics.h"

#define VALID_MAP_CHARACTERS " 01234NSEW"
#define DIRECTIONS "NSEW"

int count_check_columns(char const *line);
int check_top_bottom_borders(void);
int check_left_right_borders(void);
int check_valid(void);
int	copy_map(void);
int parse_map(void);
bool map_has_wall_at(float x, float y);
bool is_inside_map(float x, float y);
void render_map(void);
int	get_map_at(int i, int j);
void check_all_type(void);

#endif
