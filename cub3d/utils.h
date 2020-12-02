#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "config.h"

/*typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}		t_str;*/

int		ft_in_set(char c, char const *set);
int		is_space(int x);
int		is_upper(int x);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *str);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char **ft_split(char const *src, char sep);
t_str *str_add_back(t_str **str, char *content);
t_str *str_last(t_str *str);
void error_detected_exit(char const *str);

#endif
