#ifndef PLAYER_H
#define PLAYER_H

#include "defs.h"
#include "config.h"
#include "map.h"
#include "graphics.h"
#include <math.h>

typedef struct {
	float x;
	float y;
	float width;
	float height;
	int turn_direction; // -1 for left, +1 for right
	int walk_direction; // -1 for back, +1 for front
	float rotation_angle;
	float walk_speed;
	float turn_speed;
} player_t;

extern player_t player;

void get_player_starting_point(void);
void move_player(void);
void render_player(void);

#endif
