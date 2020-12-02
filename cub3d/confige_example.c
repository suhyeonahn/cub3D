#include "cub3d.h"

int	g_fd;
int	g_ret;

static int	parse_resolution(t_config *config, char *line)
{
	int		i;
	int		width;
	int		height;

	i = 0;
	width = 0;
	height = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		width = width * 10 + line[i++] - 48;
	while (is_space(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		height = height * 10 + line[i++] - 48;
	config->width = width;
	config->height = height;
	return (1);
}

static char	*parse_path(char *line)
{
	int		i;
	char	*buff;

	i = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	buff = ft_strdup(line + i);
	return (buff);
}

static int	parse_color(char *line)
{
	int	i;
	int	j;
	int	color;
	int	colors[3];

	i = 0;
	j = 0;
	while (j < 3)
		colors[j++] = 0;
	while (is_upper(line[i]))
		i++;
	if (is_space(line[i]))
		i++;
	j = -1;
	while (line[i] && ++j < 3)
	{
		while (line[i] && ft_isdigit(line[i]))
			colors[j] = colors[j] * 10 + line[i++] - 48;
		if ((!ft_strchr(",", line[i]) && line[i] != '\0') || colors[j] > 255)
			return (-1);
		ft_strchr(",", line[i]) ? i++ : 0;
	}
	color = colors[0] * 256 * 256 + colors[1] * 256 + colors[2];
	return (color);
}

static int	parse_map(t_config *config, char *temp)
{
	int		i;
	int		j;

	if (!(config->map = ft_split(temp, '\n')))
		return (0);
	free(temp);
	i = -1;
	j = 0;
	while (config->map[++i])
		j = j < (int)ft_strlen(config->map[i])
			? (int)ft_strlen(config->map[i]) : j;
	config->rows = i;
	config->colums = j;
	config->tile = config->width / config->colums;
	return (1);
}

int			parse_by_type(int ret, t_config *c, int tp, char *line)
{
	static char *temp = "";

	if (tp == C_R)
	{
		if (!parse_resolution(c, line))
			return (free_line(line, 0));
	}
	else if (tp >= C_NO && tp <= C_S)
	{
		if (c->tex[tp].tex_path || !(c->tex[tp].tex_path = parse_path(line)))
			return (free_line(line, 0));
	}
	else if (tp == C_F || tp == C_C)
	{
		if ((tp == C_F && (c->floor_color = parse_color(line)) == -1) ||
				(tp == C_C && (c->ceiling_color = parse_color(line)) == -1))
			return (free_line(line, 0));
	}
	else
	{
		temp = update_temp(temp, line);
		if (ret == 0 && !parse_map(c, temp))
			return (free_line(line, 0));
	}
	return (free_line(line, 1));
}
static int	is_cub_file(char const *conf_path)
{
	int ret;
	int len;

	ret = 1;
	len = ft_strlen(conf_path);
	if (len >= 4)
		ret = ft_strncmp(conf_path + len - 4, ".cub", 4);
	return (ret == 0 ? 1 : 0);
}

static int	check_map_component(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("012NSEW ", line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static int	check_type(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	else if (check_map_component(line))
		return (C_MAP);
	return (-1);
}

static int	is_blank_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int			parse_config(t_game *game, t_config *config, char const *conf_path)
{
	int				type;
	char			*line;

	if (!(is_cub_file(conf_path)))
		return (exit_error(game, EXIT_FAILURE, "ERROR\nNOT .CUB EXTENSION\n"));
	if ((g_fd = open(conf_path, O_RDONLY)) < 0)
		return (exit_error(game, EXIT_FAILURE, "ERROR\nWRONG FILE PATH\n"));
	g_ret = 1;
	while ((g_ret = get_next_line(g_fd, &line)) > 0)
	{
		if ((type = check_type(line)) == -1)
			return (exit_error(game, EXIT_FAILURE, "ERROR\nwrong type"));
		if (is_blank_line(line) && !(config->map))
		{
			free(line);
			continue;
		}
		else if (is_blank_line(line) && config->map && g_ret)
			return (exit_error(game, EXIT_FAILURE, "blank line in the map"));
		if (!parse_by_type(g_ret, config, type, line))
			return (0);
	}
	parse_by_type(g_ret, config, type, line);
	close(g_fd);
	return (1);
}
