/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:06:30 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 19:06:32 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fill_f_table(int n_w_in_r, int nbr_rows, int n_w, t_ls *flags)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < n_w_in_r * nbr_rows)
	{
		j = -1;
		while (++j < nbr_rows)
		{
			if (i < n_w)
			{
				flags->table[j][k] = flags->files[i];
				flags->table[j][k + 1] = NULL;
			}
			i++;
		}
		flags->table[j] = NULL;
		k++;
	}
}

void	ft_fill_r_table(int n_w_in_r, int nbr_rows, int n_w, t_ls *flags)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	i = n_w - 1;
	while (i > -1)
	{
		j = -1;
		while (++j < nbr_rows)
		{
			if (i <= n_w)
			{
				flags->table[j][k] = flags->files[i];
				flags->table[j][k + 1] = NULL;
			}
			i--;
		}
		flags->table[j] = NULL;
		k++;
	}
}

void	ft_create_table(int nbr_rows, int n_w, t_ls *flags, int n_w_in_r)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	j = -1;
	flags->table = (char***)malloc(sizeof(char**) * (nbr_rows + 1));
	ft_bzero(flags->table, (nbr_rows + 1) * sizeof(char**));
	while (++j < nbr_rows)
	{
		flags->table[j] = (char**)malloc(sizeof(char*) * (n_w + 1));
		ft_bzero(flags->table[j], (n_w + 1) * sizeof(char*));
	}
	if (!flags->r && !flags->one && !flags->l)
		ft_fill_f_table(n_w_in_r, nbr_rows, n_w, flags);
	else if (flags->files[0] && !flags->one && !flags->l)
		ft_fill_r_table(n_w_in_r, nbr_rows, n_w, flags);
}

void	ft_print_table(t_ls *flags, int max_len)
{
	int	i;
	int	j;

	i = -1;
	while (flags->table[++i])
	{
		j = -1;
		while (flags->table[i][++j])
			ft_printf("%-*s", max_len, flags->table[i][j]);
		ft_printf("\n");
		free(flags->table[i]);
	}
}

void	ft_make_table(t_ls *flags, int n_w, int n_w_in_r, int max_len)
{
	int	i;
	int	j;
	int	nbr_rows;

	nbr_rows = ft_get_nbr_rows(n_w, n_w_in_r, max_len);
	if (!(flags->l) && (!(flags->one)))
		ft_create_table(nbr_rows, n_w, flags, n_w_in_r);
	if (flags->l)
	{
		ft_detailed_list(flags, n_w);
		return ;
	}
	if (flags->one)
	{
		ft_print_column(flags, n_w);
		return ;
	}
	else if (!flags->one && !flags->l)
		ft_print_table(flags, max_len);
	free(flags->table);
}
