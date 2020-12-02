/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:35:34 by suahn             #+#    #+#             */
/*   Updated: 2020/02/25 14:36:39 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
