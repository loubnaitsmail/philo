/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:47:33 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/01 19:48:01 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)(haystack));
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i + j] == needle[j])
		{
			while (needle[j] && haystack[i + j] == needle[j] && i + j < len)
				j++;
			if (!needle[j])
				return ((char *)(&haystack[i]));
		}
		i++;
	}
	return (NULL);
}
