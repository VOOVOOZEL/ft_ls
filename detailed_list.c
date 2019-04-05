/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detailed_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 23:18:21 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/04 23:18:23 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_detailed_list(t_ls flags, int i)
{
	t_date	date;
	int		len_links;
	int		len_owner;
	int		len_sizes;

	len_links = ft_find_len_for_output(flags.hd_links, 1);
	len_owner = ft_find_len_for_output(flags.owner, 5);
	len_sizes = ft_find_len_for_output(flags.sizes, 1);
	ft_parse_date(flags, i, &date);
	ft_printf("%s ", flags.acc_right[i]);
	ft_printf("%*s ", (len_links), flags.hd_links[i]);
	ft_printf("%s  ", flags.owner[i]);
	ft_printf("%s ", flags.group[i]);
	ft_printf("%*s ", (len_sizes + 1), flags.sizes[i]);
	ft_printf("%s %s %s ", date.month, date.day, date.time);
	ft_printf("%s\n", flags.files[i]);
}

void	ft_detailed_list(t_ls flags, int nbr_words)
{
	int i;

	i = -1;
	if (flags.r)
	{
		i = nbr_words;
		if (flags.p_st_m[flags.cur_dir] != 33188
		&& flags.p_st_m[flags.cur_dir] != 108)
			ft_printf("total %d\n", flags.block);
		while (i--)
			ft_print_detailed_list(flags, i);
	}
	else
	{
		if (flags.p_st_m[flags.cur_dir] != 33188
		&& flags.p_st_m[flags.cur_dir] != 108)
			ft_printf("total %d\n", flags.block);
		while (flags.files[++i])
			ft_print_detailed_list(flags, i);
	}
}

void	ft_push_struct(t_ls *flags)
{
	flags->rl = 0;
	flags->l = 0;
	flags->a = 0;
	flags->r = 0;
	flags->t = 0;
	flags->p = 0;
	flags->u = 0;
	flags->ul = 0;
	flags->one = 0;
	flags->dash = 0;
	flags->l_f = 0;
	flags->fls = -1;
	flags->block = 0;
}
