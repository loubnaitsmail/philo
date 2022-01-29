/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:04:59 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/19 19:05:08 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*old_lst;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		old_lst = *lst;
		*lst = old_lst->next;
		free(old_lst);
	}
	*lst = NULL;
}
