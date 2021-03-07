#include "player.h"

player_t player = {
	.x = 0,
	.y = 0,
	.width = 1,
	.height = 1,
	.turn_direction = 0,
	.walk_direction = 0,
	.rotation_angle = PI / 2,
	.walk_speed = 10,
	.turn_speed = 10 * (PI / 180)
};

void get_player_starting_point(void)
{
	int i = 0;
	while (i < config.rows)
	{
		int j = 0;
		while (j < config.columns)
		{
			if (config.map[i][j] == 'N' - '0' || config.map[i][j] == 'S' - '0' || config.map[i][j] == 'E' - '0' || config.map[i][j] == 'W' - '0')
			{
				player.x = j * TILE_SIZE;
				player.y = i * TILE_SIZE;
				break;
			}
			j++;
		}
		i++;
	}
}

/*void movePlayer(float deltaTime)
  {
  player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
  float moveStep = player.walkDirection * player.walkSpeed * deltaTime;
  }*/

void move_player(void)
{
	//float deltaTime = 0.10f;

	player.rotation_angle += player.turn_direction * player.turn_speed;
	int move_step = player.walk_direction * player.walk_speed;

	float new_playerX = player.x + cos(player.rotation_angle) * move_step;
	float new_playerY = player.y + sin(player.rotation_angle) * move_step;

	//PERFORM WALL COLLISION
	if (!map_has_wall_at(new_playerX, new_playerY))
	{
		player.x = new_playerX;
		player.y = new_playerY;
	}
}

void render_player(void)
{
	draw_rect(
			MINIMAP_SCALE_FACTOR * player.x,
			MINIMAP_SCALE_FACTOR * player.y,
			MINIMAP_SCALE_FACTOR * player.width,
			MINIMAP_SCALE_FACTOR * player.height, 
			0xFF00FF
			);
}
