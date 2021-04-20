#include "ray.h"

ray_t rays[NUM_RAYS];

void calculate_sprites(void)
{
    float first_x;
    float last_x;
    //float y;
    float center_x;
	float center_y;
	float inc;

	sprites_buffer = sprites_buffer_head;
	while (sprites_buffer)
    {
		center_x = sprites_buffer->x * TILE_SIZE - 0.5 * TILE_SIZE;
		center_y = sprites_buffer->y * TILE_SIZE - 0.5 * TILE_SIZE;

		inc = player.rotation_angle - 90 * (PI / 180);
		normalize_angle(&inc);

		first_x = center_x - TILE_SIZE / 2;
		last_x = center_x + TILE_SIZE / 2;
		
		//y = inc * x + center_y - inc * center_x;
		//y = floor(y);
        sprite = sprite_add_back(&sprite, first_x, last_x, center_y, inc, center_y - inc * center_x);
		sprites_buffer = sprites_buffer->next;
    }
	//sprite = sprite_head;
	// Free sprites_buffer

}

/*t_sprite_in_ray *sprite_ray_add_back(t_sprite_in_ray **sprite, float first_x, float last_x, float y, float center, float width, float height)
{
	t_sprite_in_ray	*first;
	t_sprite_in_ray    *new;
	
	if (!first_x || !last_x || !y || !center || !width || !height)
		return (NULL);
	if (!(new = (t_sprite*)malloc(sizeof(*new))))
		return (0);
	new->first_x = first_x;
    new->last_x = last_x;
    new->y = y;
    new->center = center;
    new->width = width;
    new->height = height;
	new->next = NULL;
	if (!*sprite)
	{
		*sprite = new;
		sprite_head = *sprite;
	}
	else
	{
		first = *sprite;
		while ((*sprite)->next) // error occurs
			*sprite = (*sprite)->next;
		(*sprite)->next = new;
		*sprite = first;
	}
	return (new);
}*/

void cast_a_ray(float ray_angle, int strip_id)
{
	normalize_angle(&ray_angle);//we are changing actual value of parameter

	int is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	int is_ray_facing_up = !is_ray_facing_down;

	int is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int is_ray_facing_left = !is_ray_facing_right;

	float xintercept, yintercept;
	float xstep, ystep;

	///////////////////////////////////////////
	/////HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool found_horz_wall_hit = false;
	float horz_wall_hitX = 0;
	float horz_wall_hitY = 0;
	int horz_wall_content = 0;

	//Find the y_coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += is_ray_facing_down ? TILE_SIZE : 0;

	//Find the x_coordinate of the closest horizontal grid intersectionyèyyy§§
	xintercept = player.x + (yintercept - player.y) / tan(ray_angle);

	//Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	float next_horz_touchX = xintercept;
	float next_horz_touchY = yintercept;
	
	//Increment xstep and ystep until we find a wall
	while (is_inside_map(next_horz_touchX, next_horz_touchY))
	{
		float x_to_check = next_horz_touchX;
		float y_to_check = next_horz_touchY + (is_ray_facing_up ? -1 : 0);

		if (map_has_wall_at(x_to_check, y_to_check))
		{
			// found a wall hit...
			horz_wall_hitX = next_horz_touchX;
			horz_wall_hitY = next_horz_touchY;
			horz_wall_content = get_map_at((int)floor(next_horz_touchY / TILE_SIZE), (int)floor(next_horz_touchX / TILE_SIZE));
			found_horz_wall_hit = true;
			break;
		}
		else
		{
			next_horz_touchX += xstep;
			next_horz_touchY += ystep;
		}
	}

/*
	//Find the y_coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += is_ray_facing_down ? TILE_SIZE : 0;

	//Find the x_coordinate of the closest horizontal grid intersection
	xintercept = floor(player.x + (yintercept - player.y) / tan(ray_angle));

	//Calculate the increment xstep and ystep
	xstep = 1;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = tan(ray_angle);
	ystep *= is_ray_facing_up ? -1 : 1;*/


	yintercept -= 0.5 * TILE_SIZE;
	bool found_sprite_hit = false;
	float next_touchX_sprite = xintercept;
	float next_touchY_sprite = yintercept;
	int i = 0;
	float sprite_hitX[5];
	float sprite_hitY[5];
	int k = 0;

	// ERROR
	
	while (is_inside_map(next_touchX_sprite, next_touchY_sprite))
	{
		sprite = sprite_head;
		if (map_has_sprite_at(&sprite, next_touchX_sprite, floor(next_touchY_sprite)))
		{
			found_sprite_hit = true;
			sprite_hitX[i] = next_touchX_sprite;
			sprite_hitY[i] = sprite->inc * next_touchX_sprite + sprite->b;

    		//sprite_hitY[i] = next_touchY_sprite;
			i++;
		}
			next_touchX_sprite += xstep;
			next_touchY_sprite += ystep;
			k++;
	}
	////////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool found_vert_wall_hit = false;
	float vert_wall_hitX = 0;
	float vert_wall_hitY = 0;
	int vert_wall_content = 0;

	// Find the y_coordinate of the closest horizontal grid intersection
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += is_ray_facing_right ? TILE_SIZE : 0;

	// Find the y_coordinate of the closest horizontal grid intersection
	yintercept = player.y + (xintercept - player.x) * tan(ray_angle);

	// Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = TILE_SIZE * tan(ray_angle);
	ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

	float next_vert_touchX = xintercept;
	float next_vert_touchY = yintercept;
	// Increment xstep and ystep until we find a wall
	while (is_inside_map(next_vert_touchX, next_vert_touchY))
	{
		float x_to_check = next_vert_touchX + (is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touchY;
		if (map_has_wall_at(x_to_check, y_to_check))
		{
			// Found a wall hit...
			vert_wall_hitX = next_vert_touchX;
			vert_wall_hitY = next_vert_touchY;
			vert_wall_content = get_map_at((int)floor(next_vert_touchY / TILE_SIZE),(int)floor(next_vert_touchX / TILE_SIZE));
			found_vert_wall_hit = true;
			break;
		}
		else
		{
			next_vert_touchX += xstep;
			next_vert_touchY += ystep;
		}
	}

	// Calculate both horizontal and vertical hit distances and choose the smallest one
	float horz_hit_distance = found_horz_wall_hit
		? distance_between_points(player.x, player.y, horz_wall_hitX, horz_wall_hitY)
		: FLT_MAX;
	float vert_hit_distance = found_vert_wall_hit
		? distance_between_points(player.x, player.y, vert_wall_hitX, vert_wall_hitY)
		: FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		rays[strip_id].distance = vert_hit_distance;
		rays[strip_id].wall_hitX = vert_wall_hitX;
		rays[strip_id].wall_hitY = vert_wall_hitY;
		rays[strip_id].wall_hit_content = vert_wall_content;
		rays[strip_id].was_hit_vertical = true;
		rays[strip_id].ray_angle = ray_angle;
	}
	else
	{
		rays[strip_id].distance = horz_hit_distance;
		rays[strip_id].wall_hitX = horz_wall_hitX;
		rays[strip_id].wall_hitY = horz_wall_hitY;
		rays[strip_id].wall_hit_content = horz_wall_content;
		rays[strip_id].was_hit_vertical = false;
		rays[strip_id].ray_angle = ray_angle;
	}
	rays[strip_id].was_hit_sprite = 0;
	if (found_sprite_hit)
	{
		int k = 0;
		int sprite_distance[i];
		
		while (i > 0)
		{
			sprite_distance[i -1] = distance_between_points(player.x, player.y, sprite_hitX[i - 1], sprite_hitY[i - 1]);
			if (sprite_distance[i - 1] < rays[strip_id].distance)
			{
				k++;
				rays[strip_id].was_hit_sprite = 1;
			}
			i--;
		}
		rays[strip_id].sprite_hitX = (float *)malloc(sizeof(float) * k);
		rays[strip_id].sprite_hitY = (float *)malloc(sizeof(float) * k);
		rays[strip_id].num_sprite = 0;
		while (k > 0)
		{
			rays[strip_id].sprite_hitX[rays[strip_id].num_sprite] = sprite_hitX[k - 1];
			rays[strip_id].sprite_hitY[rays[strip_id].num_sprite] = sprite_hitY[k - 1];
			rays[strip_id].num_sprite++;
			k--;
		}
	}
}

void cast_all_rays(void)
{
	float ray_angle = player.rotation_angle - (FOV_ANGLE / 2);
	
	for (int col = 0; col < NUM_RAYS; col++)
	{
		cast_a_ray(ray_angle, col);
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

void render_rays(void)
{
	for (int i = 0; i < NUM_RAYS; i += 50)
	{
		draw_line(
				MINIMAP_SCALE_FACTOR * player.x,
				MINIMAP_SCALE_FACTOR * player.y,
				MINIMAP_SCALE_FACTOR * rays[i].wall_hitX,
				MINIMAP_SCALE_FACTOR * rays[i].wall_hitY,
				0x00FF00
				);
	}

}
