/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:39:36 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/04 22:55:28 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <limits.h>
# include <sys/ioctl.h>
# include "./ft_printf/printf/libftprintf.h"
# define ALF "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1"

typedef struct dirent	t_dir;
typedef struct winsize	t_win;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_ls
{
	int					one;
	int					rl;
	int					l;
	int					a;
	int					r;
	int					t;
	int					p;
	int					u;
	int					ul;
	int					l_f;
	int					dash;
	char				*path[1024];
	char				*files[1024];
	char				***table;
	time_t				times[1024];
	time_t				ctimes[1024];
	time_t				atimes[1024];
	char				*acc_right[1024];
	char				*sizes[1024];
	char				*owner[1024];
	char				*group[1024];
	char				*hd_links[1024];
	char				*r_path[1024];
	int					block;
	int					p_st_m[1024];
	int					fls;
	int					cur_dir;
}						t_ls;

typedef struct			s_date
{
	char				month[4];
	char				day[3];
	char				time[7];
}						t_date;

char					ft_get_type(t_dir ent);
int						ft_get_nbr_rows(int nbr_words,
						int nbr_words_in_row, int max_len);
int						ft_count_words(t_ls flags);
int						ft_find_len_for_output(char **names, int del);
int						ft_size_term();
void					ft_handle_common(t_ls *flags, int dir_nbr);
void					ft_handle_one(t_ls flags, int dir_nbr);
void					ft_handle_r(t_ls flags, t_stat buff);
int						ft_count_dirs(t_ls *flags, t_stat buff);
void					ft_parse_dirs(t_ls *flags, const char **av);
void					ft_get_files(char *dir_name, t_ls flags);
int						ft_get_dirs(char *dir_name, t_ls flags,
						char **gen_path, DIR *dir);
void					ft_get_files_r(char *dir_name, t_ls flags);
char					ft_check_xrights(char *fpath);
void					*ft_get_acc_rights(t_dir ent, t_stat buff);
void					*ft_get_acc_rights_f(t_stat buff);
void					ft_set_data_f(t_stat buff, int j, t_ls *flags);
void					ft_set_data(t_dir *ent, t_stat buff,
						int j, t_ls *flags);
void					ft_error_handle(t_stat	buff, char *dir_name);
void					ft_get_year_f(t_date *date, char *tmp);
void					ft_get_year(t_date *date, char *tmp);
void					ft_get_time(t_date *date, char *tmp);
void					ft_parse_date(t_ls flags, int i, t_date *date);
void					ft_fill_f_table(int nbr_words_in_row,
						int nbr_rows, int nbr_words, t_ls *flags);
void					ft_fill_r_table(int nbr_words_in_row, int nbr_rows,
						int nbr_words, t_ls *flags);
void					ft_create_table(int nbr_rows, int nbr_words,
						t_ls *flags, int nbr_words_in_row);
void					ft_print_column(t_ls flags, int nbr_words);
void					ft_make_table(t_ls flags, int nbr_words,
						int nbr_words_in_row, int max_len);
void					ft_print_detailed_list(t_ls flags, int i);
void					ft_swap(char **s1, char **s2);
void					ft_swap_time(time_t *s1, time_t *s2);
void					ft_swap_fields(t_ls *flags, int j);
void					ft_sort_alph_and_print(t_ls flags,
						int nbr_words_in_row, int max_len);
void					ft_print_files(t_ls flags);
void					ft_print_detailed_list(t_ls flags, int i);
void					ft_detailed_list(t_ls flags, int nbr_words);
void					ft_push_struct(t_ls *flags);
void					ft_wrong_flag(t_ls *flags, char str);
void					ft_base_flags(char str, t_ls *flags);
void					ft_check_flags(t_ls *flags, char str, int i);
void					ft_set_flags(t_ls *flags, const char **av);
void					ft_parse_flags(t_ls *flags, const char **av);
void					ft_print_files(t_ls flags);
void					ft_free_struct(t_ls *flags);
#endif
