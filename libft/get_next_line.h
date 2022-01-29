/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:21:05 by litsmail          #+#    #+#             */
/*   Updated: 2021/01/21 17:07:07 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

int		contain(char *str, char c);
int		separate(char **line, char *save_buf, int index);
int		read_last(char **line, char *save_buf);
int		read_func(int fd, char **line, int res);
int		get_next_line(const int fd, char **line);
char	*ft_realloc(char *ptr, size_t new_size);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlen(const char *src);
char	*ft_strdup(const char *s1);
char	*ft_memalloc(size_t n);
char	*ft_strcat(char *dest, char *src);

#endif
