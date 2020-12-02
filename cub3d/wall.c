#include "wall.h"

void render_wall_projection(void)
{
	int bpp = 32;
	int size_line = WINDOW_WIDTH * 4;
	int endian = 0;
	void *img_ptr = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	int *img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

	for (int i = 0; i < NUM_RAYS; i++)
	{
		//		float correctWallDistance = rays[i].distance * cos(fabs(rays[i].rayAngle - player.rotationAngle));
		float projected_wall_height = (TILE_SIZE / rays[i].distance) * DIST_PROJ_PLANE;

		int wall_strip_height = (int)projected_wall_height;

		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

		int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;
		/*	int textureOffsetX;
			if (rays[i].wasHitVertical)
			{
			textureOffsetX = (int)rays[i].wallHitY % TILE_SIZE;
			}
			else
			{
			textureOffsetX = (int)rays[i].wallHitX % TILE_SIZE;
			}
			for (int y = 0; y < wallTopPixel; y++)
			{
			int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
			int textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);
			img_data[(WINDOW_WIDTH * y) + i] = wallTexture[(texture_width * textureOffsetY) + textureOffsetX];
			}
			for (int y = wallTopPixel; y < wallBottomPixel; y++)
			img_data[(WINDOW_WIDTH * y) + i] = 0xAABBFF;*/
		for (int y = 0; y < wall_top_pixel; y++)
			img_data[(WINDOW_WIDTH * y) + i] = 0x00AAFF;
		int texture_offsetX;
		if (rays[i].was_hit_vertical)
		{
			texture_offsetX = (int)rays[i].wall_hitY % TILE_SIZE;
		}
		else
		{
			texture_offsetX = (int)rays[i].wall_hitX % TILE_SIZE;
		}
		for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		{
			int distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
			int texture_offsetY = distance_from_top * ((float)texture[i].height / wall_strip_height);

			int is_ray_facing_down = rays[i].ray_angle > 0 && rays[i].ray_angle < PI;
			int is_ray_facing_up = !is_ray_facing_down;

			int is_ray_facing_right = rays[i].ray_angle < 0.5 * PI || rays[i].ray_angle > 1.5 * PI;
			int is_ray_facing_left = !is_ray_facing_right;

			int is_player_facing_down = player.rotation_angle > 0 && player.rotation_angle < PI;
			int is_player_facing_up = !is_player_facing_down;

			int is_player_facing_right = player.rotation_angle < 0.5 * PI || player.rotation_angle > 1.5 * PI;
			int is_player_facing_left = !is_player_facing_right;

			if ((is_player_facing_down && !rays[i].was_hit_vertical) || (is_player_facing_left && rays[i].was_hit_vertical && is_ray_facing_up) || (is_player_facing_right && rays[i].was_hit_vertical && is_ray_facing_up))
				img_data[(WINDOW_WIDTH * y) + i] = texture[0].tex[(int)(texture[i].width * texture_offsetY) + texture_offsetX];
			if ((is_player_facing_up && !rays[i].was_hit_vertical) || (is_player_facing_left && rays[i].was_hit_vertical && is_ray_facing_down) || (is_player_facing_right && rays[i].was_hit_vertical && is_ray_facing_down))
				img_data[(WINDOW_WIDTH * y) + i] = texture[1].tex[(int)(texture[i].width * texture_offsetY) + texture_offsetX];
			if ((is_player_facing_right && !rays[i].was_hit_vertical) || (is_player_facing_down && rays[i].was_hit_vertical && is_ray_facing_left) || (is_player_facing_up && rays[i].was_hit_vertical && is_ray_facing_left))
				img_data[(WINDOW_WIDTH * y) + i] = texture[2].tex[(int)(texture[i].width * texture_offsetY) + texture_offsetX];
			if ((is_player_facing_left && !rays[i].was_hit_vertical) || (is_player_facing_down && rays[i].was_hit_vertical && is_ray_facing_right) || (is_player_facing_up && rays[i].was_hit_vertical && is_ray_facing_right))
				img_data[(WINDOW_WIDTH * y) + i] = texture[3].tex[(int)(texture[i].width * texture_offsetY) + texture_offsetX];
		}
		/*
		   for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		   {
		   int distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
		   int texture_offsetY = distance_from_top * ((float)texture_height / wall_strip_height);
		   img_data[(WINDOW_WIDTH * y) + i] = wall_texture[(texture_width * texture_offsetY) + texture_offsetX];
		   }*/
		for (int y = wall_bottom_pixel; y < WINDOW_HEIGHT; y++)
			img_data[(WINDOW_WIDTH * y) + i] = 0xAABBFF;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}
