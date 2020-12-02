#include "map.h"

int count_check_columns(char const *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '1')
			j++;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (j);
}

int check_top_bottom_borders(void)
{
	int		first_line;
	int		last_line;
	t_str	*last;

	if (!map_buffer->content)
		return (0);
	first_line = count_check_columns(map_buffer->content);
	last = str_last(map_buffer);
	if (last)
		last_line = count_check_columns(last->content);
	else
		last_line = 0;
	if (first_line == last_line)
		return (first_line);
	return (0);
}

int check_left_right_borders(void)
{
	int				i;
	int				first;
	int				last;

	if (!map_buffer->content)
		return (0);
	i = 0;
	while (map_buffer->content)
	{
		first = 0;
		while (map_buffer->content[first] == ' ')
			first++;
		last = ft_strlen(map_buffer->content) - 1;
		while (last > 0 && last == ' ')
			last--;
		if (last <= 1
				|| map_buffer->content[first] != '1'
				|| map_buffer->content[last] != '1')
			return (0);
		map_buffer = *map_buffer->next;
		i++;
	}
	return (i);
}

int check_map_valid(void)
{
	int	i;
	int	col;

	while (map_buffer->content)
	{
		i = 0;
		col = 0;
		while (map_buffer->content[i])
		{
			if (!ft_in_set(map_buffer.content[i], VALID_MAP_CHARACTERS))
				return (0);
			if (map_buffer.content[i++] != ' ')
				col++;
		}
		if (col != config.columns)
			return (0);
		map_buffer = *map_buffer-next;
	}
	return (1);
}

int	copy_map(void)
{
	int		i;
	int		j;
	int		has_camera;

	i = 0;
	has_camera = 0;
	while (map_buffer.content)
	{
		j = 0;
		while (map_buffer.content[j])
		{
			while (map_buffer.content[j] == ' ')
				j++;
			config.map[i][j] = map_buffer.content[j];
			if (ft_in_set(map_buffer.content[j], DIRECTIONS))
				has_camera++;
			j++;
		}
		config.map[i][j] = '\0';
		map_buffer = *map_buffer.next;
		i++;
	}
	return (has_camera);
}

int	parse_map(void)
{
	config.map = NULL;
	if ((config.columns = check_top_bottom_borders()) < 3
			|| (config.rows = check_left_right_borders()) < 3
			|| !check_map_valid())
		error_detected_exit("Error:\nmap parsing error");
	if (copy_map() != 1)
		error_detected_exit("Error:\nmap parsing error");
	//	if (copy_map(config, map_buffer, map) != 1)
	//		return (0);
	//	config->map = map;
	return (1);
}

void	check_all_type()
{
	int i;

	if (!config.width || !config.height)
		error_detected_exit("Error:\nparsing map error");
	i = 0;
	while (i++ < NUM_TEXTURES)
	{
		if (!texture[i].tex_path)
			error_detected_exit("Error:\nparsing map error");
	}
	if (!config.floor_color || !config.ceiling_color)
		error_detected_exit("Error:\nparsing map error");
}

bool map_has_wall_at(float x, float y)
{
	if (x < 0 || x > config.columns * TILE_SIZE || y < 0 || y >= config.rows * TILE_SIZE)
		return true;
	int map_grid_indexX = floor(x / TILE_SIZE);
	int map_grid_indexY = floor(y / TILE_SIZE);
	return config.map[map_grid_indexY][map_grid_indexX] != 0;
}

bool is_inside_map(float x, float y)
{
	return (x >= 0 && x <= config.columns * TILE_SIZE && y >= 0 && y <= config.rows * TILE_SIZE);
}

int	get_map_at(int i, int j)
{
	return config.map[i][j];
}

void render_map()
{
	for (int i = 0; i < config.rows; i++)
	{
		for (int j = 0; j < config.columns; j++)
		{
			int tileX = j * TILE_SIZE;
			int tileY = i * TILE_SIZE;
			uint32_t tile_color = config.map[i][j] != 0 ? 0xFFFFFF : 0x000000;
			draw_rect(
					tileX * MINIMAP_SCALE_FACTOR,
					tileY * MINIMAP_SCALE_FACTOR,
					TILE_SIZE * MINIMAP_SCALE_FACTOR,
					TILE_SIZE * MINIMAP_SCALE_FACTOR,
					tile_color * MINIMAP_SCALE_FACTOR
					);

		}
	}
}
