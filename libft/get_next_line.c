/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:21:05 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/03 19:58:09 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 420

int	contain(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	separate(char **line, char *save_buf, int index)
{
	int	i;

	*line = ft_memalloc(index + 1);
	i = -1;
	while (++i < index)
		line[0][i] = save_buf[i];
	ft_strcpy(save_buf, &save_buf[index + 1]);
	return (1);
}

int	read_last(char **line, char *save_buf)
{
	int	res;

	res = 0;
	if (save_buf != NULL)
	{
		if (contain(save_buf, '\n') != -1)
			return (separate(line, save_buf, contain(save_buf, '\n')));
		else
		{
			*line = ft_memalloc(ft_strlen(save_buf) + 1);
			*line = ft_strcpy(*line, save_buf);
			res = 2;
		}
	}
	if (*line == NULL)
		*line = ft_memalloc(1);
	return (res);
}

int	read_func(int fd, char **line, int res)
{
	long long int	size_buf;
	static char		*save_buf;
	static char		buf[BUFFER_SIZE + 1];

	size_buf = read(fd, buf, BUFFER_SIZE);
	while (size_buf > 0)
	{
		buf[size_buf] = '\0';
		if (save_buf == NULL)
			save_buf = ft_memalloc(size_buf + 1);
		else if (save_buf != NULL)
			save_buf = ft_realloc(save_buf, size_buf + ft_strlen(save_buf) + 1);
		ft_strcat(save_buf, buf);
		if (contain(save_buf, '\n') != -1)
			return (separate(line, save_buf, contain(save_buf, '\n')));
	}
	res = read_last(line, save_buf);
	if (res == 2)
	{
		free(save_buf);
		save_buf = NULL;
		return (0);
	}
	return (res);
}

int	get_next_line(const int fd, char **line)
{
	int		res;
	char	buf_valid[BUFFER_SIZE + 1];

	res = 0;
	if (fd < 0 || !line || read(fd, buf_valid, 0) == -1 || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	return (read_func(fd, line, res));
}
