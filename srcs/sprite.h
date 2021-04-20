#ifndef SPRITE_H
#define SPRITE_H

#include "defs.h"
#include <stdlib.h>
#include <unistd.h>


typedef struct s_sprites_buffer
{
    float x;
    float y;
    struct s_sprites_buffer *next;
}   t_sprites_buffer;

typedef struct s_sprite
{
    float first_x;
    float last_x;
	float y;
    float inc;
    float b;
    struct s_sprite *next;
}   t_sprite;

extern t_sprites_buffer *sprites_buffer;
extern t_sprite *sprite;
extern t_sprites_buffer *sprites_buffer_head;
extern t_sprite *sprite_head;


float distance_between_points(float x1, float y1, float x2, float y2);
t_sprites_buffer    *sprites_buffer_add_back(t_sprites_buffer **sprites_buffer, int x, int y);
t_sprite    *sprite_add_back(t_sprite **sprite, float first_x, float last_x, float y, float inc, float b);

#endif