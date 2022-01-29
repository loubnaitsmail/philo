/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:06:25 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/03 01:04:44 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_final;
	t_list	*lst_tmp;

	if (!f || !lst)
		return (NULL);
	lst_final = ft_lstnew(f(lst->content));
	if (!lst_final)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	lst = lst->next;
	while (lst)
	{
		lst_tmp = ft_lstnew(f(lst->content));
		if (!lst_tmp)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&lst_final, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_final, lst_tmp);
		lst = lst->next;
	}
	return (lst_final);
}
