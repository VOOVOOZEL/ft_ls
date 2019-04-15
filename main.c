/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:02:46 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/04 22:30:20 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, const char **av)
{
	int		j;
	int		dir_nbr;
	t_ls	flags;
	t_stat	buff;

	dir_nbr = -1;
	ft_push_struct(&flags);
	ft_parse_flags(&flags, av);
	ft_parse_dirs(&flags, av);
	j = -1;
	if (flags.rl)
		ft_handle_r(&flags, buff);
	if (!(flags.path[++j]))
		ft_get_files(".", &flags);
	dir_nbr = ft_count_dirs(&flags, buff);
	if ((flags.one))
		ft_handle_one(&flags, dir_nbr);
	ft_handle_common(&flags, dir_nbr);
}
