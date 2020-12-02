//#include <SDL2/SDL.h>
#include "defs.h"
#include "config.h"
#include "utils.h" 
#include "player.h"
#include "texture.h"
#include "ray.h"
#include "wall.h"
#include "map.h"

bool g_is_game_running = false;
//int ticksLastFrame = 0;

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

void update(void)
{
	//waste some time until we reach the target frame time length;
	//	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_LENGTH));

	//	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//	ticksLastFrame = SDL_GetTicks();
	move_player();
	cast_all_rays();
}

bool init_window(void)
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, config.width, config.height, "Cub3d");

	if (!win_ptr)
	{
		fprintf(stderr, "Error creating window.\n");
		return false;
	}

	return true;
}

void render(void)
{
	render_wall_projection();
	render_map();
	render_rays();
	render_player();
}

void clear_color_buffer(void)
{
	int j = 0;
	while (j < WINDOW_HEIGHT)
	{
		int i = 0;
		while (i < WINDOW_WIDTH)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x000000);
			i++;
		}
		j++;
	}
}

int management(void)
{
	clear_color_buffer();
	update();
	render();

	return(0);
}

void release_resources(void)
{
	destroy_texture();
	//	destroyWindow();
}

/*void error_detected_exit(char const *str)
{
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	exit(1);
}*/

int main(int argc, char **argv)
{
	if (!(argc == 2 || (argc == 3 && !ft_strncmp(argv[2], "--save", 6))))
		error_detected_exit("Error:\nargument error");
	parse_config(argv[1]);
	//	error_detected_exit("Error\nparsing map error");
		check_all_type();
	//	error_detected_exit("Error\ntype error");
	if (!parse_map())
		error_detected_exit("ERROR\ninvalid map");
	g_is_game_running = init_window();

	setup();

	mlx_hook(win_ptr, 2, 0, key_press, &player);
	mlx_hook(win_ptr, 3, 0, key_release, &player);
	//	mlx_hook(win_ptr, 17, 0, &destroyWindow, &player);
	mlx_loop_hook(mlx_ptr, management, (void *)0);
	mlx_loop(mlx_ptr);

//	release_resources();

	return 0;
}
