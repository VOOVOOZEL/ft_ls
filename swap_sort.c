/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:38:51 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 12:38:53 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

void	ft_swap_time(time_t *s1, time_t *s2)
{
	time_t tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

void	ft_swap_fields(t_ls *flags, int j)
{
	ft_swap(&flags->files[j], &flags->files[j + 1]);
	ft_swap_time(&flags->times[j], &flags->times[j + 1]);
	ft_swap_time(&flags->ctimes[j], &flags->ctimes[j + 1]);
	ft_swap_time(&flags->atimes[j], &flags->atimes[j + 1]);
	if (flags->l)
	{
		ft_swap(&flags->sizes[j], &flags->sizes[j + 1]);
		ft_swap(&flags->hd_links[j], &flags->hd_links[j + 1]);
		ft_swap(&flags->owner[j], &flags->owner[j + 1]);
		ft_swap_data(flags->acc_right[j], flags->acc_right[j + 1]);
		ft_swap(&flags->group[j], &flags->group[j + 1]);
	}
}

void	ft_sort_time(int nbr_words, t_ls *flags)
{
	int i;
	int j;

	i = -1;
	while (++i < nbr_words)
	{
		j = -1;
		while (++j < nbr_words - 1)
		{
			if ((flags->t && ((flags->times[j]) < flags->times[j + 1])))
				ft_swap_fields(flags, j);
		}
	}
}

void	ft_sort_alph_and_print(t_ls *flags, int nbr_words_in_row, int max_len)
{
	int i;
	int	j;
	int nbr_words;

	nbr_words = ft_count_words(flags);
	i = -1;
	while (++i < nbr_words)
	{
		j = -1;
		while (++j < nbr_words - 1)
		{
			if ((((ft_strcmp(flags->files[j], flags->files[j + 1]) > 0 &&
			('.' != flags->files[j][0])))))
				ft_swap_fields(flags, j);
		}
	}
	i = -1;
	ft_sort_time(nbr_words, flags);
	if (nbr_words)
		ft_make_table(flags, nbr_words, nbr_words_in_row, max_len);
}
