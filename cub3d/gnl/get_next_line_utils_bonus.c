/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:31:36 by suahn             #+#    #+#             */
/*   Updated: 2020/02/25 14:31:40 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		srclen;
	int		i;

	srclen = 0;
	while (src[srclen])
	{
		srclen++;
	}
	copy = NULL;
	if (!(copy = (char *)malloc(srclen + 1)))
		return (NULL);
	i = 0;
	while (i < srclen)
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

	ss1 = ft_strlen(s1);
	ss2 = ft_strlen(s2);
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

char	*ft_strchr(const char *s, int c)
{
	int		i;

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	if (s == NULL)
		return (NULL);
	if ((sub = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
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
