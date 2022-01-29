/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:31:51 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/12 17:26:29 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_else(size_t i, size_t size, unsigned char *destination,
		const unsigned char *source)
{
	i = size;
	while (i > 0)
	{
		i--;
		destination[i] = source[i];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t				i;
	unsigned char		*destination;
	const unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	i = 0;
	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (dest < src)
	{
		while (i < size)
		{
			destination[i] = source[i];
			i++;
		}
	}
	else
		ft_else(i, size, destination, source);
	return (dest);
}
