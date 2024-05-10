/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:49:27 by kkauhane          #+#    #+#             */
/*   Updated: 2024/02/09 16:32:58 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == 0)
		return (0);
	newlst -> content = content;
	newlst -> next = NULL;
	return (newlst);
}
