/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:27:09 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/03 00:58:28 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_filltab(int size, long nbr, int n, char *result)
{
	int	i;

	i = size - 1;
	while (i > 0)
	{
		result[i] = nbr % 10 + 48;
		nbr /= 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	else
		result[0] = nbr + 48;
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			size;
	long long	tmp;
	long long	nbr;

	nbr = n;
	tmp = 10;
	size = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		size++;
	}
	while (tmp <= nbr)
	{
		tmp *= 10;
		size++;
	}
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	return (ft_filltab(size, nbr, n, result));
}
