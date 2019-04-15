/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:28:09 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 19:28:12 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_handle_files(char *dir_name, t_ls *flags)
{
	int		j;
	t_stat	buff;
	char	buffer[100];
	char	*tmp;

	j = -1;
	flags->files[++j] = ft_strdup(dir_name);
	if (!lstat(dir_name, &buff))
	{
		ft_set_data_f(buff, j, flags);
		if (flags->l && buff.st_mode == 41453)
			ft_get_link(dir_name, flags, j);
	}
	flags->files[++j] = NULL;
}

void	ft_handle_dir(t_ls *flags, char *path, t_dir *ent, DIR *dir)
{
	t_stat	buff;
	int		j;
	char	*typ;

	j = -1;
	while ((ent = readdir(dir)))
	{
		if (ent->d_name[0] != '.' || flags->a)
		{
			typ = ft_strjoin(path, ent->d_name);
			flags->files[++j] = ft_strdup(ent->d_name);
			if (!lstat(typ, &buff) && ent->d_type == DT_LNK && flags->l)
				ft_get_link(typ, flags, j);
			ft_set_data(ent, buff, j, flags);
			free(typ);
			if (flags->p && ent->d_type == DT_DIR)
				ft_add_slash(j, flags);
		}
	}
	flags->files[++j] = NULL;
}

void	ft_get_files(char *dir_name, t_ls *flags)
{
	DIR		*dir;
	t_dir	*ent;
	t_stat	buff;
	char	*path;

	path = ft_strjoin(dir_name, "/");
	lstat(dir_name, &buff);
	ft_error_handle(buff, dir_name);
	if ((!(dir = opendir(dir_name))
	&& (buff.st_mode != 32767 && buff.st_mode != 16384) && buff.st_mode))
		ft_handle_files(dir_name, flags);
	else if ((buff.st_mode != 32767 && buff.st_mode != 16384)
	&& buff.st_mode)
		ft_handle_dir(flags, path, ent, dir);
	free(path);
	if (dir)
		closedir(dir);
	if (!(flags->files[0]))
		return ;
	ft_print_files(flags);
}

int		ft_get_dirs(char *dir_name, t_ls *flags, char **gen_path, DIR *dir)
{
	int		i;
	char	*path;
	t_dir	*ent;

	i = -1;
	while ((ent = readdir(dir)))
	{
		if ((ent->d_type == DT_DIR && ft_strcmp(ent->d_name, ".")
		&& ft_strcmp(ent->d_name, "..")))
		{
			if (ft_strcmp(dir_name, "/"))
				path = ft_strjoin(dir_name, "/");
			else
				path = ft_strdup("/");
			if (ent->d_name[0] != '.' || flags->a)
			{
				gen_path[++i] = ft_strjoin(path, ent->d_name);
				gen_path[i + 1] = NULL;
			}
			else
				continue;
			free(path);
		}
	}
	return (i);
}

void	ft_get_files_r(char *dir_name, t_ls *flags)
{
	DIR		*dir;
	char	*gen_path[1024];
	int		i;

	ft_bzero(gen_path, 1024);
	ft_get_files(dir_name, flags);
	if (!(dir = opendir(dir_name)))
		return ;
	i = ft_get_dirs(dir_name, flags, gen_path, dir);
	if (flags->r && i != -1)
	{
		while (i >= 0 && ft_printf("\n%s%s\n", gen_path[i], ":"))
		{
			ft_get_files_r(gen_path[i], flags);
			i--;
		}
	}
	else
	{
		i = -1;
		while (gen_path[++i] && ft_printf("\n%s%s\n", gen_path[i], ":"))
			ft_get_files_r(gen_path[i], flags);
	}
	closedir(dir);
	ft_free_gen(gen_path);
}
