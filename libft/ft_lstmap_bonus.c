/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:26:37 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/16 14:00:29 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// node	*ft_lstmap(node *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	node	*newlist;
// 	node	*node;
// 	void	*set;

// 	newlist = 0;
// 	if (!lst || !f || !del)
// 		return (0);
// 	while (lst)
// 	{
// 		set = f(lst -> content);
// 		node = ft_lstnew(set);
// 		if (!node)
// 		{
// 			del(set);
// 			ft_lstclear(&newlist, del);
// 			return (0);
// 		}
// 		ft_lstadd_back(&newlist, node);
// 		lst = lst -> next;
// 	}
// 	return (newlist);
// }
