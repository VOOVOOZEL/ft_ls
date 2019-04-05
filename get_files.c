#include "ft_ls.h"

void	ft_get_link(char *dir_name, t_ls *flags, int j)
{
	char	buffer[100];
	char	*tmp;

	ft_bzero(buffer, 100);
	readlink (dir_name, buffer, 100);
	tmp = ft_strjoin(flags->files[j]," -> ");
	//free(flags->files[j]);
	flags->files[j] = tmp;
	free(tmp);
	tmp = ft_strjoin(flags->files[j], buffer);
	free(flags->files[j]);
	flags->files[j] = ft_strdup(tmp);
}

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
}

void	ft_handle_dir(t_ls *flags, char *path, t_dir *ent, DIR *dir)
{
	t_stat	buff;
	int 	j;
	char 	*typ;

	j = -1;
	while ((ent=readdir(dir)))
	{
		if (ent->d_name[0] != '.' || flags->a)
		{
			typ = ft_strjoin(path,ent->d_name);
			flags->files[++j] = ft_strdup(ent->d_name);
			if (!lstat(typ, &buff) && ent->d_type == DT_LNK && flags->l)
				ft_get_link(typ, flags, j);
			ft_set_data(ent, buff, j, flags);
			free(typ);
			if (flags->p && ent->d_type == DT_DIR)
			{
				flags->files[j] = ft_strjoin(flags->files[j],"/");
			}
		}
	}
}

void    ft_get_files(char *dir_name, t_ls flags)
{
    DIR         *dir;
    t_dir       *ent;
	t_stat		buff;
	int         j;
	char 		*path = ft_strjoin(dir_name, "/");
    
	j = -1;
	ft_bzero(flags.files, 1024);
	lstat(dir_name, &buff);
	ft_error_handle(buff, dir_name);
	if((!(dir = opendir(dir_name))
	&& (buff.st_mode != 32767 && buff.st_mode != 16384) && buff.st_mode))
		ft_handle_files(dir_name, &flags);
	else if ((buff.st_mode != 32767 && buff.st_mode != 16384)
	&& buff.st_mode)
		ft_handle_dir(&flags, path, ent, dir);
	free(path);
	if (dir)
		closedir(dir);
	if (!(flags.files[0]))
		return ;
    ft_print_files(flags);
}

int ft_get_dirs(char *dir_name, t_ls flags, char **gen_path, DIR *dir)
{
	int i;
	char        *path;
	t_dir       *ent;

	i = -1;
    while ((ent=readdir(dir)))
    {
        if ((ent->d_type == DT_DIR && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, "..")))
        {
            path = ft_strjoin(dir_name, "/");
			if (ent->d_name[0] != '.' || flags.a)
			{
            	gen_path[++i] = ft_strjoin(path, ent->d_name);
				free(path);
				gen_path[i + 1] = NULL;
			}
			else
				continue;
        }
    }
	return (i);
}

void     ft_get_files_r(char *dir_name, t_ls flags)
{
    DIR         *dir;
	char		**gen_path;
	int			i;

    ft_get_files(dir_name, flags);
    if(!(dir = opendir(dir_name)))
        return ;
	gen_path = (char**)malloc(sizeof(char*) * 1024);
	i = ft_get_dirs(dir_name, flags, gen_path, dir);
	if (flags.r && i != -1)
	{
		while(gen_path[i] && ft_printf("\n%s%s\n",gen_path[i], ":"))
		{
			ft_get_files_r(gen_path[i], flags);
			i--;
		}
	}
	else
	{
		i = -1;
		while(gen_path[++i] && ft_printf("\n%s%s\n",gen_path[i], ":"))
			ft_get_files_r(gen_path[i], flags);
	}
    closedir(dir);
}