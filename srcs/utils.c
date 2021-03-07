#include "utils.h"

t_head *map_head;

void	error_detected_exit(char const *str)
{
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	exit(1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_letter(const char c, const char *letters)
{
	int i; 

	i = 0;

	while (letters[i])
	{
		if (c == letters[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (c);
		i++;
	}
	return (0);
}

void	createLinkedList(t_str *new)
{
	map_head = (t_head*)malloc(sizeof(t_head*));
	map_head->head = new;
}

t_str	*str_add_back(t_str **str, char *content)
{
	t_str	*first;
	t_str	*new;
	
	if (!content)
		return (NULL);
	if (!(new = (t_str*)malloc(sizeof(*new))))
		return (0);
	new->content = content;
	new->next = NULL;
	if (!*str)
	{
		*str = new;
		createLinkedList(new);
	}
	else
	{
		first = *str;
		while ((*str)->next)
			*str = (*str)->next;
		(*str)->next = new;
		*str = first;
	}
	return (new);
}

t_str *str_last(t_str *str)
{
	if (!str)
		return (NULL);
	while (str->next)
		str = str->next;
	return (str);
}

int str_clear(t_str **list)
{
	t_str	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		(*list) = tmp;
	}
	return (0);
}

int		is_space(int x)
{
	if ((x >= 9 && x <= 13) || x == 32)
		return (1);
	return (0);
}

int		is_upper(int x)
{
	if (x >= 65 && x <= 90)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	while ((str1[i] || str2[i]) && (i < n))
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	} 
	return (0);
}

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == '\n' || str[i] == '\v' || str[i] == '\t' ||
				str[i] == '\f' || str[i] == ' ' || str[i] == '\r'))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		src_len;
	int		i;

	src_len = 0;
	while (src[src_len])
	{
		src_len++;
	}
	copy = NULL;
	if (!(copy = (char *)malloc(src_len + 1)))
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	if (s == NULL)
		return (NULL);
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (!(start > ft_strlen(s)))
	{
		while (i < len && s[start + i])
		{
			sub[i] = s[start + i];
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;

	i = 0;
	while (c && s[i])
	{
		if (s[i] == c)
			return ((char*)s + i);
		i++;
	}
	while (c == '\0')
	{
		if (s[i] == '\0')
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	ss1;
	unsigned int	ss2;
	unsigned int	i;
	char			*new;

	ss2 = ft_strlen(s1);
	ss1 = ft_strlen(s2);
	if (!(new = (char *)malloc(sizeof(char) * (ss1 + ss2 + 1))))
		return (NULL);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}

static int	numstring(char const *s1, char c)
{
	int	count;
	int	cles;

	count = 0;
	cles = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1)
	{
		if (*s1 == c)
			cles = 0;
		else if (cles == 0)
		{
			cles = 1;
			count++;
		}
		s1++;
	}
	return (count);
}

static int	numchar(char const *s2, char c, int i)
{
	int count;

	count = 0;
	while (s2[i] && s2[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

char		**freee(char const **dst, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dst[j]);
	}
	free(dst);
	return (NULL);
}

char		**ft_split(char	const *s, char c)
{
	size_t	i;
	int		k;
	int		j;
	char	**dst;

	if (s == NULL)
		return (NULL);
	if (!(dst = (char**)malloc(sizeof(char*) * (numstring(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < numstring(s, c))
	{
		while (s[i] == c)
			i++;
		k = 0;
		if (!(dst[j] = (char*)malloc(numchar(s, c, i) + 1)))
			return (freee((char const **)dst, j));
		while (s[i] && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

int		fill_the_line(char *s, char **line, int data)
{
	int				len;

	len = 0;
	if (s)
	{
		while (s[len] != '\n' && s[len] != '\0')
			len++;
	}
	if (s && s[len] == '\n')
	{
		*line = ft_substr(s, 0, len);
	}
	if (!s && data == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (data == 0 && s[len] == '\0')
	{
		*line = ft_strdup(s);
		return (0);
	}
	return (1);
}

char	*save_the_leftline(char *s)
{
	int				len;
	int				end;
	char			*tmp;

	len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	end = 0;
	while (s[end])
		end++;
	if (s[len] == '\n' && s)
	{
		tmp = ft_substr(s, len + 1, end - len - 1);
		free(s);
		s = tmp;
	}
	return (s);
}

char	*read_next_line(const int fd, char *s, int *data)
{
	char			*tmp;
	char			buf[BUFFER_SIZE + 1];

	while ((*data = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[*data] = '\0';
		if (!s)
			s = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(s, buf);
			free(s);
			s = tmp;
		}
		if (ft_strchr(s, '\n'))
			break ;
	}
	return (s);
}

int		get_next_line(const int fd, char **line)
{
	static char		*s;
	int				result;
	int				data;

	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	s = read_next_line(fd, s, &data);
	if (data < 0)
		return (-1);
	result = fill_the_line(s, line, data);
	if (result == 0)
	{
		free(s);
		s = NULL;
		return (0);
	}
	if (result == 1)
		s = save_the_leftline(s);
	return (1);
}
