#include "ft_ls.h"

void ft_parse_dirs(t_ls *flags, const char **av)
{
    int     i;
    int     j;
	t_stat	buff;

    i = flags->l_f;
    j = -1;
    while (av[++i])
	{
        flags->path[++j] = ft_strdup(av[i]);
		stat(flags->path[j], &buff);
		flags->p_st_m[j] = buff.st_mode;
	}
	flags->path[++j] = NULL;
}

int ft_count_dirs(t_ls *flags, t_stat buff)
{
	int dir_nbr;

	dir_nbr = -1;
	while(flags->path[++flags->fls])
	{
		lstat(flags->path[flags->fls], &buff);
		if (!S_ISDIR(buff.st_mode) && !flags->l && (buff.st_mode && buff.st_mode != 41453))
			ft_printf("%s\n",flags->path[flags->fls]);
		else
			dir_nbr += 1;
	}
	return dir_nbr;
}

void ft_handle_r(t_ls flags, t_stat buff)
{
    int     j;
	int		dir_nbr;

	j = -1;
	if (!(flags.path[++j]))
		ft_get_files_r(".", flags);
	dir_nbr = ft_count_dirs(&flags, buff);
	if (dir_nbr != (flags.fls - 1))
		ft_printf("\n");
	j = -1;
	while (flags.path[++j])
	{
		lstat(flags.path[j], &buff);
		if (S_ISDIR(buff.st_mode))
		{
			if (flags.fls > 0)
				ft_printf("%s:\n", flags.path[j]);
			ft_get_files_r(flags.path[j], flags);
			if (dir_nbr--)
				ft_printf("\n");
		}
	}
	exit (0);
}

void ft_handle_one(t_ls flags, int dir_nbr)
{
	int j;
	t_stat	buff;

	j = -1;
	while (flags.path[++j])
	{
		lstat(flags.path[j], &buff);
		if (S_ISDIR(buff.st_mode) || buff.st_mode == 41453)
		{
			if (dir_nbr > 0)
				ft_printf("%s:\n", flags.path[j]);
			ft_get_files(flags.path[j], flags);
		}
		if (dir_nbr == (flags.fls - 1))
			if (dir_nbr - j)
				ft_printf("\n");
	}
	exit(0);
}

void	ft_handle_common(t_ls *flags, int dir_nbr)
{
	int	j;

	j = -1;
	while (flags->path[++j])
	{
		if (j > 0)
			ft_printf("%s:\n", flags->path[j]);
		flags->cur_dir = j;
        ft_get_files(flags->path[j], *flags);
		if (dir_nbr - j > 0)
			ft_printf("\n");
	}
	exit(0);
}