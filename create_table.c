#include "ft_ls.h"

void ft_fill_f_table(int nbr_words_in_row, int nbr_rows, int nbr_words, t_ls *flags)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 0;
	while(i < nbr_words_in_row * nbr_rows)
	{
		j = -1;
		while (++j < nbr_rows)
		{
			if (i < nbr_words)
			{
				flags->table[j][k] = flags->files[i];
				flags->table[j][k + 1] = NULL;
			}
			i++;
		}
		flags->table[j] = NULL;
		k++;
	}
}

void ft_fill_r_table(int nbr_words_in_row, int nbr_rows, int nbr_words, t_ls *flags)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	i = nbr_words - 1;
	while(i > -1)
	{
		j = -1;
		while (++j < nbr_rows)
		{
			if (i <= nbr_words)
			{
				flags->table[j][k] = flags->files[i];
				flags->table[j][k + 1] = NULL;
			}
			i--;
		}
		flags->table[j] = NULL;
		k++;
	}
}

void ft_create_table(int nbr_rows, int nbr_words, t_ls *flags, int nbr_words_in_row)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	j = -1;
	flags->table = (char***)malloc(sizeof(char**) * (nbr_rows + 1));
	while (++j < nbr_rows)
		flags->table[j] = (char**)malloc(sizeof(char*) * (nbr_words + 1));
	if (!flags->r && !flags->one && !flags->l)
		ft_fill_f_table(nbr_words_in_row, nbr_rows, nbr_words, flags);
	else if (flags->files[0] && !flags->one && !flags->l)
		ft_fill_r_table(nbr_words_in_row, nbr_rows, nbr_words, flags);
}

void ft_print_column(t_ls flags, int nbr_words)
{
	int i;

	i = -1;
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

void ft_make_table(t_ls flags, int nbr_words, int nbr_words_in_row, int max_len)
{
	int 	i;
	int		j;
	int		nbr_rows;

	nbr_rows = ft_get_nbr_rows(nbr_words, nbr_words_in_row, max_len);
	ft_create_table(nbr_rows, nbr_words, &flags, nbr_words_in_row);
	if (flags.l)
	{
		ft_detailed_list(flags, nbr_words);
		return ;
	}
	i = -1;
	if (flags.one)
	{
		ft_print_column(flags, nbr_words);
		return ;
	}
	else if (!flags.one && !flags.l)
	{
		while (flags.table[++i])
		{
			j = -1;
			while(flags.table[i][++j])
				ft_printf("%-*s",max_len,flags.table[i][j]);
			ft_printf("\n");
		}
	}
}