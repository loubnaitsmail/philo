/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:32:52 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/12 17:18:43 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int value, size_t size)
{
	size_t			i;
	unsigned char	*dest_p;
	unsigned char	dest_value;

	dest_p = p;
	dest_value = value;
	i = 0;
	while (i < size)
	{
		dest_p[i] = dest_value;
		i++;
	}
	return (p);
}
