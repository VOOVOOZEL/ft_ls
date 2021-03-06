/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:42:42 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/03/07 20:42:44 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_countnumber(intmax_t v, int b)
{
	long	i;

	i = 0;
	if (v < 0)
	{
		i = i + 1;
		v = v * -1;
	}
	while (v > 0)
	{
		i = i + 1;
		v = v / b;
	}
	return (i);
}
