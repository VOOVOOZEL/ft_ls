/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:44:13 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 12:44:14 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_files(t_ls flags)
{
	int	i;
	int	j;
	int	max_len;
	int	term_len;
	int	nbr_words_in_row;

	i = -1;
	j = -1;
	max_len = ft_find_len_for_output(flags.files, 8);
	term_len = ft_size_term();
	if (max_len)
		nbr_words_in_row = term_len / max_len;
	ft_sort_alph_and_print(flags, nbr_words_in_row, max_len);
	i = -1;
	j = ft_count_words(flags);
	while (++i < j)
		free(flags.files[i]);
}

char	ft_check_xrights(char *fpath)
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(fpath, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		return ('@');
	else
	{
		acl = acl_get_file(fpath, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			return ('+');
		else
			return (' ');
	}
}
