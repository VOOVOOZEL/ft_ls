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

void	ft_get_acc_rights(t_dir ent, t_stat buff, char *tmp)
{
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
}

void	ft_get_acc_rights_f(t_stat buff, char *tmp)
{
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
}

void	ft_get_minor(t_stat *buff, int j, t_ls *flags)
{
	int				len;
	char			*tmp;
	char			*tmp2;
	unsigned int	dev_major;
	unsigned int	dev_minor;

	dev_major = major(buff->st_rdev);
	dev_minor = minor(buff->st_rdev);
	tmp = ft_itoa(dev_major);
	flags->sizes[j] = ft_strjoin(tmp, ", ");
	free(tmp);
	tmp = ft_itoa(dev_minor);
	len = ft_strlen(tmp);
	if (len < 3)
		while (len < 3)
		{
			tmp2 = flags->sizes[j];
			flags->sizes[j] = ft_strjoin(flags->sizes[j], " ");
			free(tmp2);
			len++;
		}
	flags->sizes[j] = ft_strjoin(flags->sizes[j], tmp);
	free(tmp);
}

void	ft_set_data_f(t_stat buff, int j, t_ls *flags)
{
	char		*buffer;
	t_group		*gr;
	t_passwd	*pw;

	if (!S_ISREG(buff.st_mode) && !S_ISDIR(buff.st_mode))
		ft_get_minor(&buff, j, flags);
	else
		flags->sizes[j] = ft_itoa(buff.st_size);
	flags->times[j] = buff.st_mtime;
	flags->atimes[j] = buff.st_atime;
	flags->ctimes[j] = buff.st_ctime;
	flags->hd_links[j] = ft_itoa(buff.st_nlink);
	pw = getpwuid(buff.st_uid);
	flags->owner[j] = pw->pw_name;
	gr = getgrgid(buff.st_gid);
	flags->group[j] = gr->gr_name;
	ft_get_acc_rights_f(buff, flags->acc_right[j]);
	flags->block += buff.st_blocks;
}

void	ft_set_data(t_dir *ent, t_stat buff, int j, t_ls *flags)
{
	char		*buffer;
	t_group		*gr;
	t_passwd	*pw;

	if (!S_ISREG(buff.st_mode) && !S_ISDIR(buff.st_mode))
		ft_get_minor(&buff, j, flags);
	else
		flags->sizes[j] = ft_itoa(buff.st_size);
	flags->times[j] = buff.st_mtime;
	flags->atimes[j] = buff.st_atime;
	flags->ctimes[j] = buff.st_ctime;
	flags->hd_links[j] = ft_itoa(buff.st_nlink);
	pw = getpwuid(buff.st_uid);
	flags->owner[j] = pw->pw_name;
	gr = getgrgid(buff.st_gid);
	flags->group[j] = gr->gr_name;
	ft_get_acc_rights(*ent, buff, flags->acc_right[j]);
	flags->block += buff.st_blocks;
}
