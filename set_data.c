/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:43:14 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/05 12:43:16 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_get_acc_rights(t_dir ent, t_stat buff)
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

void	*ft_get_acc_rights_f(t_stat buff)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(char) * 11);
	tmp[0] = buff.st_mode == 41453 ? 'l' : '-';
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

void	ft_set_data_f(t_stat buff, int j, t_ls *flags)
{
	char		*buffer;
	t_group		*gr;
	t_passwd	*pw;

	flags->sizes[j] = ft_itoa(buff.st_size);
	flags->times[j] = buff.st_mtime;
	flags->atimes[j] = buff.st_atime;
	flags->ctimes[j] = buff.st_ctime;
	flags->hd_links[j] = ft_itoa(buff.st_nlink);
	pw = getpwuid(buff.st_uid);
	flags->owner[j] = pw->pw_name;
	gr = getgrgid(buff.st_gid);
	flags->group[j] = gr->gr_name;
	flags->acc_right[j] = ft_get_acc_rights_f(buff);
	flags->block += buff.st_blocks;
}

void	ft_set_data(t_dir *ent, t_stat buff, int j, t_ls *flags)
{
	char		*buffer;
	t_group		*gr;
	t_passwd	*pw;

	flags->sizes[j] = ft_itoa(buff.st_size);
	flags->times[j] = buff.st_mtime;
	flags->atimes[j] = buff.st_atime;
	flags->ctimes[j] = buff.st_ctime;
	flags->hd_links[j] = ft_itoa(buff.st_nlink);
	pw = getpwuid(buff.st_uid);
	flags->owner[j] = pw->pw_name;
	gr = getgrgid(buff.st_gid);
	flags->group[j] = gr->gr_name;
	flags->acc_right[j] = ft_get_acc_rights(*ent, buff);
	flags->block += buff.st_blocks;
}

void	ft_error_handle(t_stat buff, char *dir_name)
{
	if (!(buff.st_mode) || buff.st_mode == 32767)
	{
		ft_printf("ls: %s: No such file or directory\n", dir_name);
		return ;
	}
	if (!(buff.st_mode & S_IWUSR) && !(buff.st_mode & S_IRUSR)
	&& !(buff.st_mode & S_IXUSR))
	{
		ft_printf("ls: %s: Permisson denied\n", (dir_name));
		return ;
	}
}
