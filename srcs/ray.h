#ifndef RAY_H
#define RAY_H

#include "defs.h"
#include "player.h"
#include "map.h"
#include "graphics.h"
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <float.h>

typedef struct s_sprite_in_ray
{
    float center;
	float width;
    float hitX;
    float hitY;
    struct s_sprite_in_ray *next;
}   t_sprite_in_ray;

//extern t_sprite_in_ray *sprite_in_ray;

typedef struct
{
	float ray_angle;
	float wall_hitX;
	float wall_hitY;
	float distance;
	bool was_hit_vertical;
	int wall_hit_content;
	int num_sprite;
	t_sprite_in_ray *sprite_in_ray;
    float *sprite_hitX;
    float *sprite_hitY;
	bool was_hit_sprite;
} ray_t;

#define NUM_RAYS 1920
extern ray_t rays[NUM_RAYS];

void	calculate_sprites(void);
//float distance_between_points(float x1, float y1, float x2, float y2);
void	cast_all_rays(void);
void	cast_a_ray(float ray_angle, int strip_id);
void	render_rays(void);

#endif
