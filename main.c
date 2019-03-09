#include "ft_ls.h"

int ft_size_term()
{
    t_win w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return (w.ws_col);
}

int ft_find_len_for_output(t_ls flags)
{
    int i;
    int max_len;

    i = -1;
    max_len = 0;
    while (flags.files[++i])
        if (ft_strlen(flags.files[i]) > max_len)
            max_len = ft_strlen(flags.files[i]);
	if (!(max_len % 4))
		max_len = 2 * max_len;
	else
    	while(max_len % 4)
        	max_len++;
	if (max_len == 20)
		max_len+=4;
	if (max_len == 28)
		max_len+=4;
    return (max_len);
}

int	ft_count_words(t_ls flags)
{
	int i;

	i = -1;
	while((flags.files[++i]));
	return(i);
}

int	ft_isupper(int c)
{
	return (c >= 65 && c <= 90);
}

void ft_make_table(t_ls flags, int nbr_words, int nbr_words_in_row, int max_len)
{
	int i;
	int	j;
	int k;
	int	nbr_rows;
	int term_len;

	term_len = ft_size_term();
	i = 0;
	k = 0;
	//printf("ses = %d\n", term_len - (nbr_words_in_row * max_len));
	if (!(nbr_words % nbr_words_in_row) && ((term_len - (nbr_words_in_row * max_len)) > max_len))
		nbr_rows = nbr_words;
	else if (!(nbr_words % nbr_words_in_row))
		nbr_rows = nbr_words / nbr_words_in_row;
	else
		nbr_rows = (nbr_words / nbr_words_in_row) + 1;
	//printf("rows= %d\n",nbr_rows);
	// if ((term_len - (nbr_words_in_row * max_len)) < max_len)
	// 	nbr_rows = nbr_rows * 2;
	flags.table = (char***)malloc(sizeof(char**) * (nbr_rows + 1));
	j = -1;
	while (++j < nbr_rows)
		flags.table[j] = (char**)malloc(sizeof(char*) * (nbr_words + 1));
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
	i = -1;
	while(flags.table[++i])
	{
		j = -1;
		while(flags.table[i][++j])
		{
			// printf("i = %d, j = %d\n", i, j);
			printf("%-*s",max_len,flags.table[i][j]);
		}
		printf("\n");
	}
	i = -1;
	while(++i < nbr_rows)
		free(flags.table[i]);
	free(flags.table);
}

void ft_sort_alph_and_print(t_ls flags, int nbr_words_in_row, int max_len)
{
	int i;
	int	j;
	char *tmp;
	int nbr_words;
	
	nbr_words = ft_count_words(flags);
	i = nbr_words;
	while (i--)
	{
		j = nbr_words;
		while (j--)
			if(ft_isupper(flags.files[j][0]) && 
			(ft_strcmp(flags.files[i], flags.files[j]) &&
			ft_strcmp(flags.files[i], ".") &&
			ft_strcmp(flags.files[i], "..")))
			{
				tmp = flags.files[i];
				flags.files[i] = flags.files[j];
				flags.files[j] = tmp;
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
    max_len = ft_find_len_for_output(flags);
    term_len = ft_size_term();
	// printf("max_len = %d\n",max_len);
	// printf("term_len = %d\n",term_len);
	if (max_len) 
	{
		nbr_words_in_row = term_len/max_len;
		//printf("nbr_words_in_row = %d\n",nbr_words_in_row);
	}
	ft_sort_alph_and_print(flags, nbr_words_in_row , max_len);
    i = -1;
    while(flags.files[++i])
        free(flags.files[i]);
}

void    ft_get_files(char *dir_name, t_ls flags)
{
    DIR         *dir;
    t_dir       *ent;
    int         j;

    j = -1;
    if(!(dir = opendir(dir_name)))
    {
        printf("ls: %s: No such file or directory\n", dir_name);
        return ;
    }
    while ((ent=readdir(dir)))
        if (ent->d_name[0] != '.' || flags.a)
        	flags.files[++j] = ft_strdup(ent->d_name);
    flags.files[++j] = NULL;
    closedir(dir);
    ft_print_files(flags);
}

void     ft_get_files_R(char *dir_name, t_ls flags)
{
    DIR         *dir;
    t_dir       *ent;
    char        *path;
    int         j;

    j = -1;
    ft_get_files(dir_name, flags);
    if(!(dir = opendir(dir_name)))
        return ;
    while ((ent=readdir(dir)))
    {
        if (ent->d_type == DT_DIR && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
        {
            path = ft_strjoin(dir_name, "/");
			if (ent->d_name[0] != '.' || flags.a)
            	path = ft_strjoin(path, ent->d_name);
			else
				continue;
            printf("\n%s\n",ft_strjoin(path,":"));
            ft_get_files_R(path, flags);
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
    flags->dash = 0;
    flags->path = (char**)malloc(sizeof(char*) * 1024);
    flags->files = (char**)malloc(sizeof(char*) * 1024);
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
						flags->dash = 1;
				}
				else
				    printf("usage: ls [%s] [file ...]", ALF);
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

    i = 0;
    j = -1;
    while (av[++i])
    {
        if (av[i][0] != '-' )
            flags->path[++j] = ft_strdup(av[i]);
    } 
}

int main(int ac, const char **av)
{
    int     i;
    int     j;
    t_ls    flags;
    int     max_len;

    i = 0;
    j = -1;
    ft_push_struct(&flags);
    ft_parse_flags(&flags, av);
    if (ac == 1)
    {
        ft_get_files("./", flags);
        return (0);
    }
    ft_parse_dirs(&flags, av);  
    j = -1;
    if (flags.R)
    {   
        if (!(flags.path[++j]))
            ft_get_files_R("./", flags);
        j = -1;
        while (flags.path[++j])
        {
            ft_get_files_R(flags.path[j], flags);
        }
    }
    // if (!(flags.path[++j]))
    //         ft_get_files("./", flags);
    // while (flags.path[++j])
    //         ft_get_files(flags.path[j], flags);
    // return (0);
    // j = ft_find_len_for_output(flags);
    // printf("max len is %d",j);
}