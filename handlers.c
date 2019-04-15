/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:54:11 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 12:54:13 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parse_dirs(t_ls *flags, const char **av)
{
	int		i;
	int		j;
	t_stat	buff;

	i = flags->l_f;
	j = -1;
	while (av[++i])
	{
		flags->path[++j] = ft_strdup(av[i]);
		lstat(flags->path[j], &buff);
		flags->p_st_m[j] = buff.st_mode;
	}
	flags->path[++j] = NULL;
	i = -1;
	while (flags->path[++i])
	{
		j = -1;
		while (flags->path[++j])
			if (S_ISDIR(flags->p_st_m[j]) && flags->path[j + 1])
			{
				ft_swap(&flags->path[j], &flags->path[j + 1]);
				ft_swap_int(&flags->p_st_m[j], &flags->p_st_m[j + 1]);
			}
	}
}

int		ft_count_dirs(t_ls *flags, t_stat buff)
{
	int	dir_nbr;

	dir_nbr = -1;
	while (flags->path[++flags->fls])
		dir_nbr += 1;
	return (dir_nbr);
}

void	ft_handle_r(t_ls *flags, t_stat buff)
{
	int	j;
	int	dir_nbr;

	j = -1;
	if (!(flags->path[++j]))
		ft_get_files_r(".", flags);
	dir_nbr = ft_count_dirs(flags, buff);
	if (dir_nbr != (flags->fls - 1))
		ft_printf("\n");
	j = -1;
	while (flags->path[++j])
	{
		lstat(flags->path[j], &buff);
		if (flags->fls > 0 && S_ISDIR(buff.st_mode))
			ft_printf("%s:\n", flags->path[j]);
		ft_get_files_r(flags->path[j], flags);
		if (dir_nbr-- && S_ISDIR(flags->p_st_m[j + 1]))
			ft_printf("\n");
		free(flags->path[j]);
	}
	exit(0);
}

void	ft_handle_one(t_ls *flags, int dir_nbr)
{
	int		j;
	t_stat	buff;

	j = -1;
	while (flags->path[++j])
	{
		lstat(flags->path[j], &buff);
		if (dir_nbr > 0
		&& (S_ISDIR(buff.st_mode) || buff.st_mode == 41453))
			ft_printf("%s:\n", flags->path[j]);
		ft_get_files(flags->path[j], flags);
		if (dir_nbr == (flags->fls - 1))
			if (dir_nbr - j && S_ISDIR(flags->p_st_m[j + 1]))
				ft_printf("\n");
		free(flags->path[j]);
	}
	exit(0);
}

void	ft_handle_common(t_ls *flags, int dir_nbr)
{
	int		j;
	t_stat	buff;

	j = -1;
	while (flags->path[++j])
	{
		lstat(flags->path[j], &buff);
		if (flags->fls > 1 && S_ISDIR(buff.st_mode))
			ft_printf("%s:\n", flags->path[j]);
		flags->cur_dir = j;
		ft_get_files(flags->path[j], flags);
		if (dir_nbr - j > 0 && S_ISDIR(flags->p_st_m[j + 1]))
			ft_printf("\n");
		free(flags->path[j]);
	}
	exit(0);
}
