#include "utils.h"
#include <stdlib.h>

void error_detected_exit(char const *str)
{
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	exit(1);
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
		*str = new;
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

char **ft_split(char const *src, char sep)
{
	int i = 0;
	int count = 0;
	char **str;

	while (src[i++])
	{
		if (src[i] == sep)
			count++;
	}
	str = malloc(sizeof(char*) * count + 1);
	i = 0;
	int j = 0;
	int k = 0;
	while (src[i++] && j < count)
	{
		str[j][k++] = src[i];
		if (src[i] == sep)
		{
			j++;
			continue;
		}
	}
	return (str);
}

/*
   int		i;
   int		start;
   t_str	*str;

   start = 0;
   i = 0;
   str = NULL;
   while (org[i])
   {
   if (org[i] == sep)
   {
   if (i - start > 0
   && !str_add_back(&str, ft_substr(org, start, i - start)))
   return (PTR_CAST(str_clear(&str)));
   start = ++i;
   }
   else
   i++;
   }
   if (i - start > 0
   && !str_add_back(&str, ft_substr(org, start, i - start)))
   return (PTR_CAST(str_clear(&str)));
   return (str);
   }*/
