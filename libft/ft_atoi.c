/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:21:05 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/03 00:54:19 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			negatif;
	long long	convert;

	negatif = 1;
	convert = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negatif = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		convert = convert * 10 + (*str - 48);
		str++;
	}
	return ((int)(convert * negatif));
}
