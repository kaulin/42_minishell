/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:42:39 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/29 15:01:26 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_add_to_alpha(t_var *var, t_var *new)
{
	var = var->alpha;
	if (ft_strncmp(var->key, new->key, ft_strlen(var)) > 0)
	{
		new->a_next = var;
		while (var)
		{
			var->alpha = new;
			var = var->next;
		}
	}
	else
	{
		new->alpha = var;
		while (var->a_next)
		{
			if (ft_strncmp(var->a_next->key, new->key, ft_strlen(var)) > 0)
			{
				new->a_next = var->a_next;
				var->a_next = new;
			}
			else
				var = var->a_next;
		}
		var->a_next = new;
	}
}

void	var_rmv_from_alpha(t_var *var, t_var *rmv)
{
	var = var->alpha;
	if (var = rmv)
	{
		while (var)
		{
			var->alpha = rmv->a_next;
			var = var->a_next;
		}
	}
	else
	{
		while (var->a_next != rmv)
			var = var->a_next;
		var->a_next = rmv->next;
	}
}
