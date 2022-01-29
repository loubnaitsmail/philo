/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:38:47 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/03 01:02:33 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(char current, char c)
{
	if (current == c)
		return (1);
	return (0);
}

static int	count_words(char *str, char c)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] && is_char(str[i], c))
			i++;
		else if (str[i] && !is_char(str[i], c))
		{
			words++;
			while (str[i] && !is_char(str[i], c))
				i++;
		}
	}
	return (words);
}

static char	*duplicate(char *str, int nbr_caracters)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (nbr_caracters + 1));
	if (!dest)
		return (NULL);
	while (str[i] && i < nbr_caracters)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**fill_tab(char **final_str, char *str, char c, int size)
{
	int		caracters;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (count < size)
	{
		caracters = 0;
		while (str[i] && is_char(str[i], c))
			i++;
		while (str[i] && !is_char(str[i], c))
		{
			caracters++;
			i++;
		}
		final_str[count] = duplicate(&str[i - caracters], caracters);
		count++;
	}
	return (final_str);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**final_str;

	words = count_words((char *)s, c);
	final_str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!final_str)
		return (NULL);
	final_str = fill_tab(final_str, (char *)s, c, words);
	final_str[words] = 0;
	return (final_str);
}
