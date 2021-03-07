#include "graphics.h"

/*int destroyWindow(player_t *player)
{
	exit_game(player);
	free(colorBuffer);
}*/

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
	int i = x;
	while (i < (x + width))
	{
		int j = y;
		while (j < (y + height))
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
			j++;
		}
		i++;
	}
}

void draw_line (int x0, int y0, int x1, int y1, uint32_t color)
{
	int deltaX = (x1 - x0);
	int deltaY = (y1 - y0);

	int longest_side_length = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

	float x_increment = deltaX / (float)longest_side_length;
	float y_increment = deltaY / (float)longest_side_length;

	float currentX = x0;
	float currentY = y0;

	for (int i = 0; i < longest_side_length; i++)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, currentX, currentY, color);
		currentX += x_increment;
		currentY += y_increment;
	}
}
