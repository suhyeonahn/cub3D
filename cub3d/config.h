#ifndef CONFIG_H
#define CONFIG_H

#include "defs.h"
#include "utils.h" 

#define TYPE_R				8
#define TYPE_NO				0
#define TYPE_SO				1
#define TYPE_WE				2
#define TYPE_EA				3
#define TYPE_S				4
#define TYPE_F				5
#define TYPE_C				6
#define TYPE_MAP			7

#define NUM_TEXTURES 5

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

typedef struct s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

t_texture texture[NUM_TEXTURES];
t_config config;
t_str *map_buffer;

void init_texture(void);
int	is_empty_line(void);
void	parse_resolution(void);
char	*parse_texture_path(void);
int	parse_color(char *line);
int	check_map_component(void);
int	check_type(void);
void parse_line(void);
int	is_cub_file(char const *conf_path);
void	parse_config(char const *conf_path);


#endif
