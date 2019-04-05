/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 23:19:29 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 12:43:08 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_wrong_flag(t_ls *flags, char str)
{
	if (flags->files)
		ft_printf("ls: illegal option -- %c\n", str);
	ft_printf("usage: ls [%s] [file ...]", ALF);
}

void	ft_base_flags(char str, t_ls *flags)
{
	if (str == 'R')
		flags->rl = 1;
	if (str == 'l')
		flags->l = 1;
	if (str == 'a')
		flags->a = 1;
	if (str == 'r')
		flags->r = 1;
	if (str == 't')
		flags->t = 1;
	if (str == '-')
		flags->dash = 1;
}

void	ft_check_flags(t_ls *flags, char str, int i)
{
	if (ft_strchr(ALF, str))
	{
		ft_base_flags(str, flags);
		if (str == 'p')
			flags->p = 1;
		if (str == '1')
			flags->one = 1;
		if (str == 'u')
			flags->u = 1;
		if (str == 'U')
			flags->ul = 1;
		flags->l_f = i;
	}
	else
		ft_wrong_flag(flags, str);
}

void	ft_set_flags(t_ls *flags, const char **av)
{
	int		i;
	int		j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		if (av[i][++j] == '-')
		{
			if (!(av[i][j + 1]))
				return ;
			while (av[i][++j] && !flags->dash)
				ft_check_flags(flags, av[i][j], i);
		}
	}
}

void	ft_parse_flags(t_ls *flags, const char **av)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (av[++i])
	{
		if (av[i][++j] != '.' && av[i][++j + 1] != '/')
			ft_set_flags(flags, av);
		else
			return ;
	}
}
