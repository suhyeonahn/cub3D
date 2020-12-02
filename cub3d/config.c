#include "config.h"

int g_fd;
int g_ret;
int g_type = 0;
char *g_line;

t_config config = {
	.width = 0,
	.height = 0,
	.rows = 0,
	.columns = 0,
	.tile = 0,
	.floor_color = 0,
	.ceiling_color = 0,
	.map = NULL
};

t_str *map_buffer = {NULL, NULL};

void init_texture(void)
{
	int i = 0;

	while (i < NUM_TEXTURES)
		t_texture texture[i++].tex_path = NULL;
}

int	is_empty_line(void)
{
	int		i;

	i = 0;
	while (g_line[i])
	{
		if (!is_space(g_line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_resolution(void)
{
	int		i;
	char	*str[1];

	i = 1;
	while (g_line[++i])
		if (g_line[i] != ' ' && g_line[i] < '0' && g_line[i] > '9')
			error_detected_exit("Error:\ncub content type error");
	str = ft_split(g_line, ' '); // split a line into 2 seperated lines.
	i = 0;
	while (i)
		config.width = config.width * 10 + str[0][i++] - 48;
	i = 0;
	while (i)
		config.height = config.height * 10 + str[1][i++] - 48;
}

char	*parse_texture_path(void)
{
	int		i;
	char	*buff;

	i = 0;
	while (is_upper(g_line[i]))
		i++;
	while (is_space(g_line[i]))
		i++;
	buff = ft_strdup(g_line + i);
	return (buff);
}

int	parse_color(char *line)
{
	int	i;
	int	j;
	int	colors[2];
	char *str[2];

	j = 0;
	while (j < 3)
		colors[j++] = 0;

	i = 1;
	while (line[++i])
		if (line[i] != ' ' && line[i] < '0' && line[i] > '9')
			error_detected_exit("Error:\ncub content type error");
	i = 0;
	j = 0;
	str = ft_split(line, ','); // split a line into 3 seperated lines.
	while (str[i][j++])
	{
		while (ft_isdigit(str[i][j]))
			colors[j] = colors[j] * 10 + str[i][j++] - 48;
	}
	return (colors[0] * 256 * 256 + colors[1] * 256 * colors[2]);
	/*	while (g_line[i] && j < 3)
		{
		while (g_line[i] && ft_isdigit(g_line[i]))//replancement of atoi is possible
		colors[j] = colors[j] * 10 + g_line[i++] - 48;
	//if ((!ft_strchr(",", g_line[i]) && g_line[i] != '\0') || colors[j] > 255)
	//	return (-1);
	ft_strchr(",", g_line[i]) ? i++ : 0;
	}
	color = colors[0] * 256 * 256 + colors[1] * 256 + colors[2];
	return (color);
	 */
}

int	check_map_component(void)
{
	int i;

	i = 0;
	while (g_line[i])
	{
		if (ft_strchr("012NSEW ", g_line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_type(void)
{
	if (g_line[0] == 'R' && g_line[1] == ' ')
		return (TYPE_R);
	else if (g_line[0] == 'N' && g_line[1] == 'O')
		return (TYPE_NO);
	else if (g_line[0] == 'S' && g_line[1] == 'O')
		return (TYPE_SO);
	else if (g_line[0] == 'W' && g_line[1] == 'E')
		return (TYPE_WE);
	else if (g_line[0] == 'E' && g_line[1] == 'A')
		return (TYPE_EA);
	else if (g_line[0] == 'S' && g_line[1] == ' ')
		return (TYPE_S);
	else if (g_line[0] == 'F' && g_line[1] == ' ')
		return (TYPE_F);
	else if (g_line[0] == 'C' && g_line[1] == ' ')
		return (TYPE_C);
	else if (check_map_component() == 1)
		return (TYPE_MAP);
	error_detected_exit("Error:\nmap parsing error");
}

void parse_line(void)
{
	g_type = check_type();
	if (g_type == TYPE_R)
		parse_resolution();
	else if (g_type >= TYPE_NO && g_type <= TYPE_EA)
		tex[g_type].tex_path = parse_texture_path();
	else if (g_type == TYPE_F)
		config.floor_color = parse_color(g_line);
	else if (g_type == TYPE_C)
		config.ceiling_color = parse_color(g_line);
	else if (g_type == TYPE_MAP)
		map_buffer = str_add_back(&map_buffer, ft_strdup(line));
}

int	is_cub_file(char const *conf_path)
{
	int ret;
	int len;

	ret = 1;
	len = strlen(conf_path);
	if (len >= 4)
		ret = strncmp(conf_path + len - 4, ".cub", 4);
	return (ret == 0 ? 1 : 0);
}

void	parse_config(char const *conf_path)
{
	if (!(is_cub_file(conf_path)))
		error_detected_exit("Error:\nextention error");
	if((g_fd = open(conf_path, O_RDONLY < 0)))
		error_detected_exit("Error:\ncontent error");
	//g_ret = 1;
	while (get_next_line(g_fd, &g_line))
	{
		if(is_empty_line() == 1 && !map_buffer.content)
		{
			free(g_line);
			continue;
		}
		else if (is_empty_line() == 1 && map_buffer.content)
			error_detected_exit("Error:\nmap error");
		parse_line();
		free(g_line);
	}
	/*	if (g_ret && strlen(line) > 0)
		str_add_back(ft_strdup(g_line));
		free(g_line);*/
	close(g_fd);
	//if (!parse_map())
	//	str_clear();
	//str_clear();
}
