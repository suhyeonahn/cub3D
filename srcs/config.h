#ifndef CONFIG_H
#define CONFIG_H

#include "defs.h"
#include "utils.h" 
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	check_all_type(void);
int		check_type(void);
//int	is_empty_line(void);
void	parse_resolution(void);
char	*parse_texture_path(void);
int		parse_color(void);
int		check_map_component(void);
int		check_type(void);
void	parse_line(void);
int		is_cub_file(char const *conf_path);
void	parse_config(char const *conf_path);

typedef struct {
	char *tex_path;
	int	*tex;
	double width;
	double height;
}	t_texture;

typedef struct {
	int width;
	int	height;
	int rows;
	int columns;
	double tile;
	int	floor_color;
	int ceiling_color;
	int **map;
}	t_config;

extern t_texture texture[NUM_TEXTURES];
extern t_config config;
extern t_str *map_buffer;
extern int g_fd;
extern int g_type;
extern char *g_line;

#endif
