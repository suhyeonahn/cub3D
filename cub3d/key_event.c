int key_press(int keycode, player_t *player)
{
	if (keycode == KEY_UP)
		player->walkDirection = +1;
	else if (keycode == KEY_DOWN)
		player->walkDirection = -1;
	if (keycode == KEY_RIGHT)
		player->turnDirection = +1;
	else if (keycode == KEY_LEFT)
		player->turnDirection = -1;
	return (0);
}

int key_release(int keycode, player_t *player)
{
	if (keycode == KEY_UP)
		player->walkDirection = 0;
	else if (keycode == KEY_DOWN)
		player->walkDirection = 0;
	else if (keycode == KEY_RIGHT)
		player->turnDirection = 0;
	else if (keycode == KEY_LEFT)
		player->turnDirection = 0;
	return (0);
}

/*void	key_manager(player_t *player)
{
	if (game->keys->key_a == 1)
		move_left(game->layout, game->player);
	else if (game->keys->key_s == 1)
		move_backward(game->layout, game->player);
	else if (game->keys->key_d == 1)
		move_right(game->layout, game->player);
	else if (game->keys->key_w == 1)
		move_forward(game->layout, game->player);
	else if (game->keys->left_arr == 1)
		rotate_left(game->player);
	else if (game->keys->right_arr == 1)
		rotate_right(game->player);
	else if (game->keys->key_esc == 1)
		exit_game(game);
}*/
