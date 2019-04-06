/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:44:13 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 12:44:14 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_add_slash(int j, t_ls *flags)
{
	char	*typ;

	typ = ft_strjoin(flags->files[j], "/");
	free(flags->files[j]);
	flags->files[j] = typ;
}

void	ft_free_gen(char **gen_path)
{
	int	i;

	i = -1;
	while (gen_path[++i])
		free(gen_path[i]);
}

void	ft_swap_data(char s1[11], char s2[11])
{
	int		i;
	char	tmp;

	i = -1;
	while (++i < 11)
	{
		tmp = s1[i];
		s1[i] = s2[i];
		s2[i] = tmp;
	}
}
