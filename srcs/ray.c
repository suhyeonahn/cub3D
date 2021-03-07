// 레이케스팅 해독하기

#include "ray.h"

ray_t rays[NUM_RAYS];

void normalize_angle(float *angle)
{
	//cant use module% for float val
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
}

float distance_between_points(float x1, float y1, float x2, float y2)
{
	return sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
}

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

	//Find the x_coordinate of the closest horizontal grid intersection
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

		if(map_has_wall_at(x_to_check, y_to_check))
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

		if(map_has_wall_at(x_to_check, y_to_check))
		{
					
			//printf("\n%i:%i\n", (int)floor(y_to_check / TILE_SIZE), (int)floor(x_to_check / TILE_SIZE));

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
