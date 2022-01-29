/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:43:17 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/12 17:45:08 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	y;
	size_t	size_dest;

	size_dest = ft_strlen(dest);
	i = size_dest;
	y = 0;
	if (i < size)
	{
		while (src[y] && i < size - 1)
		{
			dest[i] = src[y];
			i++;
			y++;
		}
		dest[i] = '\0';
	}
	if (size < size_dest)
		return (size + ft_strlen(src));
	else
		return (size_dest + ft_strlen(src));
}
