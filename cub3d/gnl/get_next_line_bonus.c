/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:36:31 by suahn             #+#    #+#             */
/*   Updated: 2020/02/25 16:11:19 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		fill_the_line(const int fd, char **s, char **line, int data)
{
	int				len;

	len = 0;
	if (s[fd])
	{
		while (s[fd][len] != '\n' && s[fd][len] != '\0')
			len++;
	}
	if (s[fd] && s[fd][len] == '\n')
	{
		*line = ft_substr(s[fd], 0, len);
	}
	if (!s[fd] && data == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (data == 0 && s[fd][len] == '\0')
	{
		*line = ft_strdup(s[fd]);
		return (0);
	}
	return (1);
}

char	*save_the_leftline(const int fd, char **s)
{
	int				len;
	int				end;
	char			*tmp;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	end = 0;
	while (s[fd][end])
		end++;
	if (s[fd][len] == '\n' && s[fd])
	{
		tmp = ft_substr(s[fd], len + 1, end - len - 1);
		free(s[fd]);
		s[fd] = tmp;
	}
	return (s[fd]);
}

char	*read_next_line(const int fd, char **s, int *data)
{
	char			*tmp;
	char			buf[BUFFER_SIZE + 1];

	while ((*data = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[*data] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(s[fd], buf);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (s[fd]);
}

int		get_next_line(const int fd, char **line)
{
	static char		s[OPEN_MAX][BUFFER_SIZE+1];
	int				result;
	int				data;

	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	s[fd] = read_next_line(fd, &s[fd], &data);
	if (data < 0)
		return (-1);
	result = fill_the_line(fd, &s[fd], line, data);
	if (result == 0)
	{
		s[fd] = NULL;
		return (0);
	}
	if (result == 1)
		s[fd] = save_the_leftline(fd, &s[fd]);
	return (1);
}
