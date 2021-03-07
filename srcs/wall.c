#include "wall.h"

void render_wall_projection(void)
{
	int bpp = 32;
	int size_line = WINDOW_WIDTH * 4;
	int endian = 0;
	void *img_ptr = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	int *img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

	for (int x = 0; x < NUM_RAYS; x++)
	{
		float perpDistance = rays[x].distance * cos(rays[x].ray_angle - player.rotation_angle);
		float projected_wall_height = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
		if (perpDistance != 0)
			projected_wall_height = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
		else
			projected_wall_height = 0;

		int wall_strip_height = (int)projected_wall_height;

		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

		int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;
	
		for (int y = 0; y < wall_top_pixel; y++)
			img_data[(WINDOW_WIDTH * y) + x] = 0x00AAFF;

		int texture_offsetX;
		if (rays[x].was_hit_vertical)
			texture_offsetX = (int)rays[x].wall_hitY % TILE_SIZE;
		else
			texture_offsetX = (int)rays[x].wall_hitX % TILE_SIZE;
		
		/*// get the correct texture id number from the map content
		int tex_num = rays[x].wall_hit_content - 1;

        int texture_width = texture[tex_num].width;
        int texture_height = texture[tex_num].height;
*/
		for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		{
			int distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
			int texture_offsetY = distance_from_top * ((float)texture[0].height / wall_strip_height);
			int texture_offsetY1 = distance_from_top * ((float)texture[1].height / wall_strip_height);
			int texture_offsetY2 = distance_from_top * ((float)texture[2].height / wall_strip_height);
			int texture_offsetY3 = distance_from_top * ((float)texture[3].height / wall_strip_height);


			int is_ray_facing_down = rays[x].ray_angle > 0 && rays[x].ray_angle < PI;
			int is_ray_facing_up = !is_ray_facing_down;
			int is_ray_facing_right = (rays[x].ray_angle > 0 && rays[x].ray_angle < 0.5 * PI) || (rays[x].ray_angle > 1.5 * PI && rays[x].ray_angle < 2 * PI);
			int is_ray_facing_left = !is_ray_facing_right;

			int is_player_facing_east = (player.rotation_angle > 0 && player.rotation_angle < 0.25 * PI) || (player.rotation_angle > 1.75 * PI && player.rotation_angle < 2 * PI);
			int is_player_facing_south = player.rotation_angle > 0.25 * PI && player.rotation_angle < 0.75 * PI;
			int is_player_facing_west = player.rotation_angle > 0.75 * PI && player.rotation_angle < 1.25 * PI;
			int is_player_facing_north = player.rotation_angle > 1.25 * PI && player.rotation_angle < 1.75 * PI;

			if (is_player_facing_east)
			{
				if (rays[x].was_hit_vertical) // west 2
					img_data[(WINDOW_WIDTH * y) + x] = texture[2].tex[(int)(texture[2].width * texture_offsetY2) + texture_offsetX];
				else if (!rays[x].was_hit_vertical && is_ray_facing_up) // south 1
					img_data[(WINDOW_WIDTH * y) + x] = texture[1].tex[(int)(texture[1].width * texture_offsetY1) + texture_offsetX];
				else if (!rays[x].was_hit_vertical && is_ray_facing_down) // north 0
					img_data[(WINDOW_WIDTH * y) + x] = texture[0].tex[(int)(texture[0].width * texture_offsetY) + texture_offsetX];
			}
			else if (is_player_facing_south)
			{
				if (!rays[x].was_hit_vertical) // north 0
					img_data[(WINDOW_WIDTH * y) + x] = texture[0].tex[(int)(texture[0].width * texture_offsetY) + texture_offsetX];
				else if (rays[x].was_hit_vertical && is_ray_facing_right) // west 2
					img_data[(WINDOW_WIDTH * y) + x] = texture[2].tex[(int)(texture[2].width * texture_offsetY2) + texture_offsetX];
				else if (rays[x].was_hit_vertical && is_ray_facing_left) // east 3
					img_data[(WINDOW_WIDTH * y) + x] = texture[3].tex[(int)(texture[3].width * texture_offsetY3) + texture_offsetX];

			}
			else if (is_player_facing_west)
			{
				if (rays[x].was_hit_vertical) // east 3
					img_data[(WINDOW_WIDTH * y) + x] = texture[3].tex[(int)(texture[3].width * texture_offsetY3) + texture_offsetX];
				else if (!rays[x].was_hit_vertical && is_ray_facing_up) // south 1
					img_data[(WINDOW_WIDTH * y) + x] = texture[1].tex[(int)(texture[1].width * texture_offsetY1) + texture_offsetX];
				else if (!rays[x].was_hit_vertical && is_ray_facing_down) // north 0
					img_data[(WINDOW_WIDTH * y) + x] = texture[0].tex[(int)(texture[0].width * texture_offsetY) + texture_offsetX];
			}
			else if (is_player_facing_north)
			{
				if (!rays[x].was_hit_vertical) // south 1
					img_data[(WINDOW_WIDTH * y) + x] = texture[1].tex[(int)(texture[1].width * texture_offsetY1) + texture_offsetX];
				else if (rays[x].was_hit_vertical && is_ray_facing_right) // west 2
					img_data[(WINDOW_WIDTH * y) + x] = texture[2].tex[(int)(texture[2].width * texture_offsetY2) + texture_offsetX];
				else if (rays[x].was_hit_vertical && is_ray_facing_left) // east 3
					img_data[(WINDOW_WIDTH * y) + x] = texture[3].tex[(int)(texture[3].width * texture_offsetY3) + texture_offsetX];

			}
		}
/*
			if (rays[x].was_hit_vertical)
				img_data[(WINDOW_WIDTH * y) + x] = texture[3].tex[(int)(texture[3].width * texture_offsetY) + texture_offsetX];
			else if (!rays[x].was_hit_vertical)
				img_data[(WINDOW_WIDTH * y) + x] = texture[1].tex[(int)(texture[1].width * texture_offsetY1) + texture_offsetX];
		}
			if ((is_player_facing_down && !rays[x].was_hit_vertical) || (is_player_facing_left && rays[x].was_hit_vertical && is_ray_facing_up) || (is_player_facing_right && rays[x].was_hit_vertical && is_ray_facing_up))
				img_data[(WINDOW_WIDTH * y) + x] = texture[0].tex[(int)(texture[0].width * texture_offsetY1) + texture_offsetX];
			if ((is_player_facing_up && !rays[x].was_hit_vertical) || (is_player_facing_left && rays[x].was_hit_vertical && is_ray_facing_down) || (is_player_facing_right && rays[x].was_hit_vertical && is_ray_facing_down))
				img_data[(WINDOW_WIDTH * y) + x] = texture[1].tex[(int)(texture[1].width * texture_offsetY1) + texture_offsetX];
			if ((is_player_facing_right && !rays[x].was_hit_vertical) || (is_player_facing_down && rays[x].was_hit_vertical && is_ray_facing_left) || (is_player_facing_up && rays[x].was_hit_vertical && is_ray_facing_left))
				img_data[(WINDOW_WIDTH * y) + x] = texture[0].tex[(int)(texture[0].width * texture_offsetY1) + texture_offsetX];
			if ((is_player_facing_left && !rays[x].was_hit_vertical) || (is_player_facing_down && rays[x].was_hit_vertical && is_ray_facing_right) || (is_player_facing_up && rays[x].was_hit_vertical && is_ray_facing_right))
				img_data[(WINDOW_WIDTH * y) + x] = texture[3].tex[(int)(texture[3].width * texture_offsetY) + texture_offsetX];
		}
		*/

		for (int y = wall_bottom_pixel; y < WINDOW_HEIGHT; y++)  
			img_data[(WINDOW_WIDTH * y) + x] = 0xAABBFF;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}
