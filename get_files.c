#include "ft_ls.h"

void    ft_get_files(char *dir_name, t_ls flags)
{
    DIR         *dir;
    t_dir       *ent;
	t_stat		buff;
	int         j;
	char 		*path = ft_strjoin(dir_name, "/");
    
	j = -1;
	lstat(dir_name, &buff);
	ft_error_handle(buff, dir_name);
	if((!(dir = opendir(dir_name)) && (buff.st_mode != 32767 && buff.st_mode != 16384) && buff.st_mode))
	{

		flags.files[++j] = ft_strdup(dir_name);
		if (!lstat(dir_name, &buff))
		{
			ft_set_data_f(ent, buff, j, &flags);
			if (flags.l && buff.st_mode == 41453)
			{
				char buffer[100];
				ft_bzero(buffer, 100);
				readlink (dir_name, buffer, 100);
				flags.files[j] = ft_strjoin(flags.files[j]," -> ");
				flags.files[j] = ft_strjoin(flags.files[j], buffer);
			}
		}
	}
	else if ((buff.st_mode != 32767 && buff.st_mode != 16384) && buff.st_mode)
	{
		while ((ent=readdir(dir)))
		{
			if (ent->d_name[0] != '.' || flags.a)
			{
				char *typ;
				typ = ft_strjoin(path,ent->d_name);
				flags.files[++j] = ft_strdup(ent->d_name);
				if (flags.p && ent->d_type == DT_DIR)
				{
					flags.files[j] = ft_strjoin(flags.files[j],"/");
				}
				if (!lstat(typ, &buff) && ent->d_type == DT_LNK && flags.l)
				{
					char buffer[100];
					ft_bzero(buffer, 100);
					readlink (typ, buffer, 100);
					flags.files[j] = ft_strjoin(flags.files[j]," -> ");
					flags.files[j] = ft_strjoin(flags.files[j], buffer);
				}
				ft_set_data(ent, buff, j, &flags);
			}
		}
	}
	if (dir)
		closedir(dir);
    flags.files[++j] = NULL;
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