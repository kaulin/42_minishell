/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:48:58 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/09 08:05:07 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the absolute value of a number. Segfaults with INT_MIN.
int	ft_abs(int nbr)
{
	return ((nbr < 0) * -nbr + (nbr >= 0) * nbr);
}
