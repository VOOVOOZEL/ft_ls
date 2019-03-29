#include "ft_ls.h"

int ft_size_term()
{
    t_win w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return (w.ws_col);
}

int ft_find_len_for_output(char **names, int del)
{
    int i;
    int max_len;

    i = -1;
    max_len = 0;
    while (names[++i])
        if (ft_strlen(names[i]) > max_len)
            max_len = ft_strlen(names[i]);
	if (!(max_len % del) && del != 1)
		max_len = 2 * max_len;
	else
    	while(max_len % del)
        	max_len++;
    return (max_len);
}

int	ft_count_words(t_ls flags)
{
	int i;

	i = -1;
	while((flags.files[++i]));
	return(i);
}

void ft_make_table(t_ls flags, int nbr_words, int nbr_words_in_row, int max_len)
{
	int 	i;
	int		j;
	int 	k;
	int		nbr_rows;
	int 	term_len;
	t_date	date;

	i = 0;
	k = 0;
	term_len = ft_size_term();
	if (!(nbr_words % nbr_words_in_row) && ((term_len - (nbr_words_in_row * max_len)) > max_len))
		nbr_rows = nbr_words;
	else if (!(nbr_words % nbr_words_in_row))
		nbr_rows = nbr_words / nbr_words_in_row;
	else
		nbr_rows = (nbr_words / nbr_words_in_row) + 1;
	flags.table = (char***)malloc(sizeof(char**) * (nbr_rows + 1));
	j = -1;
	while (++j < nbr_rows)
		flags.table[j] = (char**)malloc(sizeof(char*) * (nbr_words + 1));
	if (!flags.r && !flags.one && !flags.l)
	{
		while(i < nbr_words_in_row * nbr_rows)
		{
			j = -1;
			while (++j < nbr_rows)
			{
				if (i < nbr_words)
				{
					flags.table[j][k] = flags.files[i];
					flags.table[j][k + 1] = NULL;
				}
				i++;
			}
			flags.table[j] = NULL;
			k++;
		}
	}
	else if (flags.files[0] && !flags.one && !flags.l)
	{
		i = nbr_words - 1;
		while(i > -1)
		{
			j = -1;
			while (++j < nbr_rows)
			{
				if (i <= nbr_words)
				{
					flags.table[j][k] = flags.files[i];
					flags.table[j][k + 1] = NULL;
				}
				i--;
			}
			flags.table[j] = NULL;
			k++;
		}
	}
	i = -1;
	if (flags.l)
	{
		if (flags.r)
		{
			i = nbr_words;
			ft_printf("total %d\n", flags.block);
			while(i--)
			{
				date.month[0] = ctime(&flags.times[i])[4];
				date.month[1] = ctime(&flags.times[i])[5];
				date.month[2] = ctime(&flags.times[i])[6];
				date.month[3] = 0;
				date.day[0] = ctime(&flags.times[i])[8];
				date.day[1] = ctime(&flags.times[i])[9];
				date.day[2] = 0;
				date.time[0] = ctime(&flags.times[i])[11];
				date.time[1] = ctime(&flags.times[i])[12];
				date.time[2] = ctime(&flags.times[i])[13];
				date.time[3] = ctime(&flags.times[i])[14];
				date.time[4] = ctime(&flags.times[i])[15];
				date.time[5] = 0;

				ft_printf("%s ", flags.acc_right[i]);
				int len_links = ft_find_len_for_output(flags.hd_links, 1);
				ft_printf("%*s ", (len_links), flags.hd_links[i]);
				int len_owner = ft_find_len_for_output(flags.owner, 10);
				ft_printf("%-*s",len_owner ,flags.owner[i]);
				int len_sizes = ft_find_len_for_output(flags.sizes, 1);
				ft_printf("%s ", flags.group[i]);
				ft_printf("%*s ",(len_sizes+1), flags.sizes[i]);
				ft_printf("%s %s %s ", date.month, date.day, date.time);
				ft_printf("%s\n",flags.files[i]);
			}
			return ;
		}
		else 
		{
			ft_printf("total %d\n", flags.block);
			while(flags.files[++i])
			{
				date.month[0] = ctime(&flags.times[i])[4];
				date.month[1] = ctime(&flags.times[i])[5];
				date.month[2] = ctime(&flags.times[i])[6];
				date.month[3] = 0;
				date.day[0] = ctime(&flags.times[i])[8];
				date.day[1] = ctime(&flags.times[i])[9];
				date.day[2] = 0;
				date.time[0] = ctime(&flags.times[i])[11];
				date.time[1] = ctime(&flags.times[i])[12];
				date.time[2] = ctime(&flags.times[i])[13];
				date.time[3] = ctime(&flags.times[i])[14];
				date.time[4] = ctime(&flags.times[i])[15];
				date.time[5] = 0;

				ft_printf("%s ", flags.acc_right[i]);
				int len_links = ft_find_len_for_output(flags.hd_links, 1);
				ft_printf("%*s ", (len_links), flags.hd_links[i]);
				int len_owner = ft_find_len_for_output(flags.owner, 10);
				ft_printf("%-*s",len_owner ,flags.owner[i]);
				int len_sizes = ft_find_len_for_output(flags.sizes, 1);
				ft_printf("%s ", flags.group[i]);
				ft_printf("%*s ",(len_sizes+1), flags.sizes[i]);
				ft_printf("%s %s %s ", date.month, date.day, date.time);
				ft_printf("%s\n",flags.files[i]);
			}
			return ;
		}	
	}
	i = -1;
	if (flags.one)
	{
		if (flags.r)
		{
			while(nbr_words--)
				ft_printf("%s\n",flags.files[nbr_words]);
		}
		else
		{
			while(++i < nbr_words)
				ft_printf("%s\n",flags.files[i]);
		}
	}
	else if (flags.files[0])
	{
		while (flags.table[++i])
		{
			j = -1;
			while(flags.table[i][++j])
				ft_printf("%-*s",max_len,flags.table[i][j]);
			ft_printf("\n");
		}
	}
	i = -1;

}


void 	ft_sort_alph_and_print(t_ls flags, int nbr_words_in_row, int max_len)
{
	int i;
	int	j;
	char *tmp;
	time_t	tmp1;
	int nbr_words;
	
	nbr_words = ft_count_words(flags);
	//printf("%nbr d\n")
	i = -1;
	if (flags.t)
	{
		while (++i < nbr_words)
		{
			j = -1;
			while (++j < nbr_words - 1)
			{
				if(((flags.times[j]) < flags.times[j + 1]))
				{
					//printf("pipa2\n");
					tmp = flags.files[j + 1];
					flags.files[j + 1] = flags.files[j];
					flags.files[j] = tmp;

					tmp1 = flags.times[j + 1];
					flags.times[j + 1] = flags.times[j];
					flags.times[j] = tmp1;
					if (flags.l)
					{
						tmp = flags.sizes[j + 1];
						flags.sizes[j + 1] = flags.sizes[j];
						flags.sizes[j] = tmp;
						
						tmp = flags.hd_links[j + 1];
						flags.hd_links[j + 1] = flags.hd_links[j];
						flags.hd_links[j] = tmp;
						
						tmp = flags.owner[j + 1];
						flags.owner[j + 1] = flags.owner[j];
						flags.owner[j] = tmp;

						tmp = flags.acc_right[j + 1];
						flags.acc_right[j + 1] = flags.acc_right[j];
						flags.acc_right[j] = tmp;

						tmp = flags.group[j + 1];
						flags.group[j + 1] = flags.group[j];
						flags.group[j] = tmp;
					}
				}
			}
		}
	}
	else
	{
		while (++i < nbr_words)
		{
			j = -1;
			while (++j < nbr_words -1)
			{
				if((ft_strcmp(flags.files[j], flags.files[j + 1]) > 0 &&
				!ft_strchr(".", flags.files[j][0])))
				{
					tmp = flags.files[j + 1];
					flags.files[j + 1] = flags.files[j];
					flags.files[j] = tmp;
					if (flags.l)
					{
						tmp = flags.sizes[j + 1];
						flags.sizes[j + 1] = flags.sizes[j];
						flags.sizes[j] = tmp;
						
						tmp = flags.hd_links[j + 1];
						flags.hd_links[j + 1] = flags.hd_links[j];
						flags.hd_links[j] = tmp;
						
						tmp = flags.owner[j + 1];
						flags.owner[j + 1] = flags.owner[j];
						flags.owner[j] = tmp;

						tmp1 = flags.times[i];
						flags.times[j + 1] = flags.times[j];
						flags.times[j] = tmp1;

						tmp = flags.acc_right[i];
						flags.acc_right[j + 1] = flags.acc_right[j];
						flags.acc_right[j] = tmp;

						tmp = flags.group[i];
						flags.group[j + 1] = flags.group[j];
						flags.group[j] = tmp;
					}
				}
			}
		}
	}
	ft_make_table(flags, nbr_words, nbr_words_in_row, max_len);
}

void    ft_print_files(t_ls flags)
{
    int i;
    int j;
    int max_len;
    int term_len;
    int nbr_words_in_row;

    i = -1;
    j = -1;
    max_len = ft_find_len_for_output(flags.files, 8);
    term_len = ft_size_term();
	if (max_len) 
		nbr_words_in_row = term_len/max_len;
	ft_sort_alph_and_print(flags, nbr_words_in_row , max_len);
    i = -1;
	j = ft_count_words(flags);
    while(++i < j)
        free(flags.files[i]);
}

char	ft_get_type(t_dir ent)
{
	if (ent.d_type== DT_UNKNOWN || ent.d_type == DT_REG)
		return('-');
	else if (ent.d_type == DT_DIR)
		return('d');
	else if (ent.d_type == DT_FIFO)
		return('p');
	else if (ent.d_type == DT_SOCK)
		return('s');
	else if (ent.d_type == DT_CHR)
		return('c');
	else if (ent.d_type == DT_BLK)
		return('b');
	else if (ent.d_type == DT_LNK)
		return('l');
	else
		return('-');
}

char		ft_check_xrights(char *fpath)
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(fpath, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		return('@');
	else
	{
		acl = acl_get_file(fpath, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			return('+');
		else
			return(' ');
	}
}

void 	*ft_get_acc_rights(t_dir ent, t_stat buff)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(char) * 11);
	tmp[0] = ft_get_type(ent);
	tmp[1] = (buff.st_mode & S_IRUSR) ? 'r' : '-';
	tmp[2] = (buff.st_mode & S_IWUSR) ? 'w' : '-';
	tmp[3] = (buff.st_mode & S_IXUSR) ? 'x' : '-';
	tmp[4] = (buff.st_mode & S_IRGRP) ? 'r' : '-';
	tmp[5] = (buff.st_mode & S_IWGRP) ? 'w' : '-';
	tmp[6] = (buff.st_mode & S_IXGRP) ? 'x' : '-';
	tmp[7] = (buff.st_mode & S_IROTH) ? 'r' : '-';
	tmp[8] = (buff.st_mode & S_IWOTH) ? 'w' : '-';
	tmp[9] = (buff.st_mode & S_IXOTH) ? 'x' : '-';
	tmp[10] = ft_check_xrights(ent.d_name);
	tmp[11] = 0;
	return (tmp);
}

void 	*ft_get_acc_rights_file(t_stat buff)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(char) * 11);
	tmp[0] = '-';
	tmp[1] = (buff.st_mode & S_IRUSR) ? 'r' : '-';
	tmp[2] = (buff.st_mode & S_IWUSR) ? 'w' : '-';
	tmp[3] = (buff.st_mode & S_IXUSR) ? 'x' : '-';
	tmp[4] = (buff.st_mode & S_IRGRP) ? 'r' : '-';
	tmp[5] = (buff.st_mode & S_IWGRP) ? 'w' : '-';
	tmp[6] = (buff.st_mode & S_IXGRP) ? 'x' : '-';
	tmp[7] = (buff.st_mode & S_IROTH) ? 'r' : '-';
	tmp[8] = (buff.st_mode & S_IWOTH) ? 'w' : '-';
	tmp[9] = (buff.st_mode & S_IXOTH) ? 'x' : '-';
	tmp[10] = ' ';
	tmp[11] = 0;
	return (tmp);
}

void    ft_get_files(char *dir_name, t_ls flags)
{
    DIR         *dir;
    t_dir       *ent;
	t_stat		buff;
	int         j;
	char 		*path = ft_strjoin(dir_name, "/");
	t_passwd 	*pw;
	struct group  *gr;

    j = -1;
	stat(dir_name, &buff);
	if(!(buff.st_mode & S_IWUSR) && !(buff.st_mode & S_IRUSR) && !(buff.st_mode & S_IXUSR))
	{
        ft_printf("ls: %s: Permisson denied\n", (dir_name));
        return ;
    }
    if(!(dir = opendir(dir_name)) && S_ISDIR(buff.st_mode))
    {
        ft_printf("ls: %s: No such file or directory\n", dir_name);
        return ;
    }
	if(!(dir = opendir(dir_name)))
	{
		j++;
		if (!stat(dir_name, &buff))
		{
			flags.files[j] = ft_strdup(dir_name);
			flags.sizes[j] = ft_itoa(buff.st_size);
			flags.times[j] = buff.st_mtime;
			flags.hd_links[j] = ft_itoa(buff.st_nlink);
			pw = getpwuid(buff.st_uid);
			flags.owner[j] = pw->pw_name;
			gr = getgrgid(buff.st_gid);
			flags.group[j] = gr->gr_name;
			flags.acc_right[j] = ft_get_acc_rights_file(buff);
			flags.block += buff.st_blocks;
		}
		ft_print_files(flags);
		return ;
	}
	while ((ent=readdir(dir)))
	{
		if (ent->d_name[0] != '.' || flags.a)
		{
			flags.files[++j] = ft_strdup(ent->d_name);
			if (!lstat(ft_strjoin(path,ent->d_name),&buff))
			{
				if (ent->d_type == DT_LNK)
				{
					char *buffer;
					readlink (ft_strjoin(path,ent->d_name), buffer, 100);
					flags.files[j] = ft_strjoin(flags.files[j]," -> ");
					flags.files[j] = ft_strjoin(flags.files[j], buffer);
				}
				flags.sizes[j] = ft_itoa(buff.st_size);
				flags.times[j] = buff.st_mtime;
				flags.hd_links[j] = ft_itoa(buff.st_nlink);
				pw = getpwuid(buff.st_uid);
				flags.owner[j] = pw->pw_name;
				gr = getgrgid(buff.st_gid);
				flags.group[j] = gr->gr_name;
				flags.acc_right[j] = ft_get_acc_rights(*ent, buff);
				flags.block += buff.st_blocks;
			}
			
		}
	}
    flags.files[++j] = NULL;
	closedir(dir);
	if (!(flags.files[0]))
		return ;
    ft_print_files(flags);
}

void     ft_get_files_R(char *dir_name, t_ls flags)
{
    DIR         *dir;
    t_dir       *ent;
    char        *path;
	char		**gen_path;
	int			i;

	i = -1;
    ft_get_files(dir_name, flags);
    if(!(dir = opendir(dir_name)))
        return ;
	gen_path = (char**)malloc(sizeof(char*) * 1024);
    while ((ent=readdir(dir)))
    {
        if (ent->d_type == DT_DIR && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
        {
            path = ft_strjoin(dir_name, "/");
			if (ent->d_name[0] != '.' || flags.a)
			{
            	gen_path[++i] = ft_strjoin(path, ent->d_name);
				free(path);
			}
			else
				continue;
        }
    }
	if (flags.r && i != -1)
	{
		while(gen_path[i])
		{
			ft_printf("\n%s%s\n",gen_path[i], ":");
			ft_get_files_R(gen_path[i], flags);
			i--;
			
		}
	}
	else
	{
		i = -1;
		while(gen_path[++i])
		{
			ft_printf("\n%s%s\n",gen_path[i], ":");
			ft_get_files_R(gen_path[i], flags);
		}
	}
    closedir(dir);
}

void    ft_push_struct(t_ls *flags)
{
    flags->R = 0;
    flags->l = 0;
    flags->a = 0;
    flags->r = 0;
    flags->t = 0;
	flags->one = 0;
    flags->dash = 0;
	flags->l_f = 0;
	flags->sizes = (char**)malloc(sizeof(char*) * 1024);
    flags->path = (char**)malloc(sizeof(char*) * 1024);
	flags->r_path = (char**)malloc(sizeof(char*) * 1024);
    flags->files = (char**)malloc(sizeof(char*) * 1024);
	flags->times = (time_t*)malloc(sizeof(time_t) * 1024);
	flags->hd_links = (char**)malloc(sizeof(char*) * 1024);
	flags->owner = (char**)malloc(sizeof(char*) * 1024);
	flags->acc_right = (char**)malloc(sizeof(char*) * 1024);
	flags->group = (char**)malloc(sizeof(char*) * 1024);
}

void    ft_set_flags(t_ls *flags, const char **av)
{
    int     i;
    int     j;

    i = 0;
    while (av[++i])
    {
        j = -1;
        if (av[i][++j] == '-')
            while (av[i][++j])
            {
				if (ft_strchr(ALF, av[i][j]))
				{
					if (av[i][j] == 'R') 
						flags->R = 1;
					if (av[i][j] == 'l') 
						flags->l = 1;
					if (av[i][j] == 'a') 
						flags->a = 1;
					if (av[i][j] == 'r') 
						flags->r = 1;
					if (av[i][j] == 't') 
						flags->t = 1;
					if (av[i][j] == '-') 
						flags->dash += 1;
					if (av[i][j] == '1') 
						flags->one = 1;
					flags->l_f = i;
				}
				else
				    ft_printf("usage: ls [%s] [file ...]", ALF);
            }
    }
}

void ft_parse_flags(t_ls *flags, const char **av)
{
    int     i;
    int     j;

    i = 0;
    j = -1;
    while (av[++i])
    {
        if (av[i][++j] != '.' && av[i][++j + 1] != '/')
            ft_set_flags(flags, av);
        else
            break;
    }
}

void ft_parse_dirs(t_ls *flags, const char **av)
{
    int     i;
    int     j;

    i = flags->l_f;
    j = -1;
    while (av[++i])
        flags->path[++j] = ft_strdup(av[i]);
	flags->path[++j] = NULL;
}

int main(int ac, const char **av)
{
    int     i;
    int     j;
	int		dir_nbr;
    t_ls    flags;
	t_stat	buff;

    i = 0;
    j = -1;
	dir_nbr = -1;
    ft_push_struct(&flags);
    ft_parse_flags(&flags, av);
    if (ac == 1)
    {
        ft_get_files(".", flags);
        return (0);
    }
    ft_parse_dirs(&flags, av);
    j = -1;
    if (flags.R)
    {   
        if (!(flags.path[++j]))
            ft_get_files_R(".", flags);
        i = -1;
		while(flags.path[++i])
		{
			stat(flags.path[i], &buff);
			if (!S_ISDIR(buff.st_mode))
				ft_printf("%s\n",flags.path[i]);
			else
				dir_nbr += 1;
		}
		if (dir_nbr != (i - 1))
			ft_printf("\n");
		j = -1;
        while (flags.path[++j])
		{
			stat(flags.path[j], &buff);
			if (S_ISDIR(buff.st_mode))
			{
				ft_printf("%s:\n", flags.path[j]);
				ft_get_files_R(flags.path[j], flags);
				if (dir_nbr--)
					ft_printf("\n");
			}
		}
		return (0);
    }
    if (!(flags.path[++j]))
            ft_get_files(".", flags);
	i = -1;
	while(flags.path[++i])
	{
		stat(flags.path[i], &buff);
		if (!S_ISDIR(buff.st_mode) && !flags.l)
			ft_printf("%s\n",flags.path[i]);
		else
			dir_nbr += 1;
	}
	j = -1;
	if ((flags.one))
	{
		while (flags.path[++j])
		{
			{
				stat(flags.path[j], &buff);
				if (S_ISDIR(buff.st_mode))
				{
					if (dir_nbr > 0)
						ft_printf("%s:\n", flags.path[j]);
					ft_get_files(flags.path[j], flags);
				}
				if (dir_nbr == (i - 1))
				{ 
					if (dir_nbr - j)
						ft_printf("\n");
				}
			}
		}
	}
	while (flags.path[++j])
	{
		if (j > 0)
			ft_printf("%s:\n", flags.path[j]);
        ft_get_files(flags.path[j], flags);
		if (dir_nbr - j)
			ft_printf("\n");
	}
}