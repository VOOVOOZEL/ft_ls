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

int ft_get_nbr_rows(int nbr_words, int nbr_words_in_row, int max_len)
{
	int 	term_len;
	int		nbr_rows;

	term_len = ft_size_term();
	if (nbr_words_in_row == 0)
	{
		ft_printf("ls: fts_open: No such file or directory");
		exit(1);
	}
	if (!(nbr_words % nbr_words_in_row) 
	&& ((term_len - (nbr_words_in_row * max_len)) > max_len))
		nbr_rows = nbr_words;
	else if (!(nbr_words % nbr_words_in_row))
		nbr_rows = nbr_words / nbr_words_in_row;
	else
		nbr_rows = (nbr_words / nbr_words_in_row) + 1;
	return nbr_rows;
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