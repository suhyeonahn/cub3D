#include "config.h"
// Global value initilizes automaticly as 0 (NULL)
int g_fd;
int g_type;
char *g_line;
t_texture texture[NUM_TEXTURES];
t_config config;
t_str *map_buffer;

void	check_all_type()
{
	int i;
	if (!config.width || !config.height)
		error_detected_exit("Error:\nparsing map error(1)\n");
	i = -1;
	while (i++ < 3)
	{
		if (!texture[i].tex_path)
			error_detected_exit("Error:\nparsing map error(2)\n");
	}
	if (!config.floor_color || !config.ceiling_color)
		error_detected_exit("Error:\nparsing map error(3)\n");
}

/*int	is_empty_line(void)
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
}*/

void	parse_resolution(void)
{
	int		i;
	char	**str;

	i = 0;
	while (is_upper(g_line[i]))
		i++;
	while (is_space(g_line[i]))
		i++;
	str = ft_split(g_line + i, ' '); // split a line into 2 seperated lines.
	i = 0;
	while (str[0][i])
		config.width = config.width * 10 + str[0][i++] - 48;
	i = 0;
	while (str[1][i])
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

int	parse_color(void)
{
	int	i;
	int	j;
	int	colors[3];
	char **str;
	
	i = 0;
	while (is_upper(g_line[i]))
		i++;
	while (is_space(g_line[i]))
		i++;
	str = ft_split(g_line + i, ','); // split a line into 3 seperated lines.
	i = 0;
	j = 0;
	while (str[i++][j])
	{
		while (is_space(str[i][j]))
			j++;
		while (ft_isdigit(str[i][++j]))
			colors[j] = colors[j] * 10 + str[i][j] - 48;
	}
	return (colors[0] * 256 * 256 + colors[1] * 256 * colors[2]);
}

int	check_map_component(void)
{
	int i;

	i = 0;
	while (g_line[i])
	{
		if (is_letter(g_line[i], "012NSEW"))
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_type(void)
{
	printf("%s\n", g_line);
	if (g_line[0] == 'R' && g_line[1] == ' ')
		return (TYPE_R);
	else if (g_line[0] == 'N' && g_line[1] == 'O')
		return (TYPE_NO); //
	else if (g_line[0] == 'S' && g_line[1] == 'O')
		return (TYPE_SO); //
	else if (g_line[0] == 'W' && g_line[1] == 'E')
		return (TYPE_WE); //
	else if (g_line[0] == 'E' && g_line[1] == 'A')
		return (TYPE_EA); //
	else if (g_line[0] == 'C' && g_line[1] == 'I')
		return (TYPE_CI); //
	else if (g_line[0] == 'F' && g_line[1] == 'L')
		return (TYPE_FL); //
	else if (g_line[0] == 'S' && g_line[1] == ' ')
		return (TYPE_S); //
	else if (g_line[0] == 'F' && g_line[1] == ' ')
		return (TYPE_F);
	else if (g_line[0] == 'C' && g_line[1] == ' ')
		return (TYPE_C);
	else if (check_map_component() == 1)
		return (TYPE_MAP);
	return (0);
}

void parse_line(void)
{
	if (!(g_type = check_type()))
		error_detected_exit("Error\nincorrect file content\n");
	if (g_type == TYPE_R)
	{
		if (config.width || config.height)
			error_detected_exit("Error\nparsing line\n");
		parse_resolution();
	}
	else if (g_type >= TYPE_NO && g_type <= TYPE_S)
	{
		if (texture[g_type -1].tex_path)
			error_detected_exit("Error\nparsing line\n");
		texture[g_type -1].tex_path = parse_texture_path();
	}
	else if (g_type == TYPE_F)
	{
		if (config.floor_color)
			error_detected_exit("Error\nparsing line\n");
		config.floor_color = parse_color();
	}
	else if (g_type == TYPE_C)
	{
		if (config.ceiling_color)
			error_detected_exit("Error\nparsing line\n");
		config.ceiling_color = parse_color();
	}
	else if (g_type == TYPE_MAP)
		map_buffer = str_add_back(&map_buffer, ft_strdup(g_line));
}

int	is_cub_file(char const *conf_path)
{
	int ret;
	int len;

	ret = 1;
	len = ft_strlen(conf_path);
	if (len >= 4)
		ret = ft_strncmp(conf_path + len - 4, ".cub", 4); // if correct, return 0 
	return (ret == 0 ? 1 : 0); // if correct, return 1 if not, return 0
}

void	parse_config(char const *conf_path)
{
	if (!(is_cub_file(conf_path)))
		error_detected_exit("Error\nincorrect file extention\n");
	if ((g_fd = open(conf_path, O_RDONLY)) < 0)
		error_detected_exit("Error\nfailed to read cub file\n");
	while (get_next_line(g_fd, &g_line))
	{
		parse_line();
		free(g_line);
	}
	map_buffer = map_head->head;
	close(g_fd);
}
