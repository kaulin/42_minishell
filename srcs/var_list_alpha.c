/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:42:39 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/30 09:20:32 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_add_to_alpha(t_var *var, t_var *new)
{
	var = var->alpha;
	if (ft_strncmp(var->key, new->key, ft_strlen(var->key)) > 0)
	{
		new->anext = var;
		while (var)
		{
			var->alpha = new;
			var = var->next;
		}
	}
	else
	{
		new->alpha = var;
		while (var->anext)
		{
			if (ft_strncmp(var->anext->key, new->key, ft_strlen(var->key)) > 0)
			{
				new->anext = var->anext;
				var->anext = new;
			}
			else
				var = var->anext;
		}
		var->anext = new;
	}
}

void	var_remove_from_alpha(t_var *var, t_var *rmv)
{
	var = var->alpha;
	if (var == rmv)
	{
		while (var)
		{
			var->alpha = rmv->anext;
			var = var->anext;
		}
	}
	else
	{
		while (var->anext != rmv)
			var = var->anext;
		var->anext = rmv->next;
	}
}
