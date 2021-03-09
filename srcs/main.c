#include "config.h"
#include "utils.h" 
#include "player.h"
#include "texture.h"
#include "ray.h"
#include "wall.h"
#include "map.h"
//#include "key_event.h"
#include "../mlx/mlx.h"

#include <stdbool.h>
#include <X11/X.h>
#include <unistd.h>

void *mlx_ptr;
void *win_ptr;

void update(void)
{
	move_player();
	cast_all_rays();
}

void render(void)
{
	render_wall_projection();
	render_map();
	render_rays();
	render_player();
}

int key_press(int keycode, player_t *player)
{
	if (keycode == KEY_UP)
		player->walk_direction = +1;
	else if (keycode == KEY_DOWN)
		player->walk_direction = -1;
	if (keycode == KEY_RIGHT)
		player->turn_direction = +1;
	else if (keycode == KEY_LEFT)
		player->turn_direction = -1;
	update();
	render();
	return (0);
}

int key_release(int keycode, player_t *player)
{
	if (keycode == KEY_UP)
		player->walk_direction = 0;
	else if (keycode == KEY_DOWN)
		player->walk_direction = 0;
	else if (keycode == KEY_RIGHT)
		player->turn_direction = 0;
	else if (keycode == KEY_LEFT)
		player->turn_direction = 0;
	return (0);
}

void setup(void)
{
	load_wall_texture();
	get_player_starting_point();
}

int management(void)
{
	//update();
	cast_all_rays();
	render();

	return(0);
}

void release_resources(void)
{
	destroy_texture();
	//	destroyWindow();
}

void init_window(void)
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, config.width, config.height, "Cub3d");

	if (!win_ptr)
	{
		error_detected_exit("Error\ncreating window");
	}
}


int main(int argc, char **argv)
{
	if (!(argc == 2 || (argc == 3 && !ft_strncmp(argv[2], "--save", 6))))
		error_detected_exit("Error\nargument error\n");
	parse_config(argv[1]);
	check_all_type();
	if (!parse_map())
		error_detected_exit("Error\ninvalid map\n");
	init_window();

	setup();

	management();

	mlx_hook(win_ptr, 2, 0, key_press, &player);
	mlx_hook(win_ptr, 3, 0, key_release, &player);
	//	mlx_hook(win_ptr, 17, 0, &destroyWindow, &player);
	//mlx_loop_hook(mlx_ptr, management, (void *)0);
	mlx_loop(mlx_ptr);

//	release_resources();
	return 0;
}
