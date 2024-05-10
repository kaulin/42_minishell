/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:25:32 by kkauhane          #+#    #+#             */
/*   Updated: 2024/02/09 16:33:49 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst)
{
	t_list	*pointer;

	while (lst != NULL)
	{
		ft_printf("%d\n", lst -> content);
		pointer = (lst)-> next;
		lst = pointer;
	}
}
