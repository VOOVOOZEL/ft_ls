#include "ft_ls.h"

void	ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

void	ft_swap_time(time_t *s1, time_t *s2)
{
	time_t tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

void	ft_swap_fields(t_ls *flags, int j)
{
	ft_swap(&flags->files[j], &flags->files[j + 1]);
	ft_swap_time(&flags->times[j], &flags->times[j + 1]);
	ft_swap_time(&flags->ctimes[j], &flags->ctimes[j + 1]);
	ft_swap_time(&flags->atimes[j], &flags->atimes[j + 1]);
	if (flags->l)
	{
		ft_swap(&flags->sizes[j], &flags->sizes[j + 1]);
		ft_swap(&flags->hd_links[j], &flags->hd_links[j + 1]);
		ft_swap(&flags->owner[j], &flags->owner[j + 1]);
		ft_swap(&flags->acc_right[j], &flags->acc_right[j + 1]);
		ft_swap(&flags->group[j], &flags->group[j + 1]);
	}
}

void	ft_sort_alph_and_print(t_ls flags, int nbr_words_in_row, int max_len)
{
	int i;
	int	j;
	int nbr_words;

	nbr_words = ft_count_words(flags);
	i = -1;
	while (++i < nbr_words)
	{
		j = -1;
		while (++j < nbr_words - 1)
		{
			if ((((ft_strcmp(flags.files[j], flags.files[j + 1]) > 0 &&
			!ft_strchr(".", flags.files[j][0])))))
				ft_swap_fields(&flags, j);
		}
	}
	i = -1;
	while (++i < nbr_words)
	{
		j = -1;
		while (++j < nbr_words - 1)
		{
			if ((flags.t && ((flags.times[j]) < flags.times[j + 1])))
				ft_swap_fields(&flags, j);
		}
	}
	i = -1;
	ft_make_table(flags, nbr_words, nbr_words_in_row, max_len);
}

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
