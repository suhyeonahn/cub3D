#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "defs.h"

#define BUFFER_SIZE 2000

typedef struct s_str {
	char			*content;
	struct s_str	*next;
}	t_str;

typedef struct s_head {
	t_str*			head;
}	t_head;

void normalize_angle(float* angle);
void	createLinkedList(t_str *new);
void error_detected_exit(char const *str);
int	    ft_isdigit(int c);
int	is_letter(const char c, const char *letters);
int	ft_in_set(char c, char const *set);
t_str	*str_add_back(t_str **str, char *content);
t_str *str_last(t_str *str);
int str_clear(t_str **list);
int		is_space(int x);
int		is_upper(int x);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *str);
char	*ft_strdup(const char *src);
char	*ft_charjoin(char c1, char c2);
char	*ft_strjoin(char const *s1, char const *s2);
char		**freee(char const **dst, int j);
char		**ft_split(char	const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		get_next_line(const int fd, char **line);

extern t_head *map_head;

#endif
