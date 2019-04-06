/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_date.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 23:15:04 by lbrown-b          #+#    #+#             */
/*   Updated: 2019/04/04 23:15:06 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_year_f(t_date *date, char *tmp)
{
	date->time[0] = ' ';
	date->time[1] = tmp[24];
	date->time[2] = tmp[25];
	date->time[3] = tmp[26];
	date->time[4] = tmp[27];
	date->time[5] = tmp[27];
	date->time[6] = 0;
}

void	ft_get_year(t_date *date, char *tmp)
{
	date->time[0] = ' ';
	date->time[1] = tmp[20];
	date->time[2] = tmp[21];
	date->time[3] = tmp[22];
	date->time[4] = tmp[23];
	date->time[5] = 0;
}

void	ft_get_time(t_date *date, char *tmp)
{
	date->time[0] = tmp[11];
	date->time[1] = tmp[12];
	date->time[2] = tmp[13];
	date->time[3] = tmp[14];
	date->time[4] = tmp[15];
	date->time[5] = 0;
}

void	ft_bonus_time(time_t *dif, int i, char **tmp, t_ls *flags)
{
	time_t	rawtime;

	time(&rawtime);
	if (flags->u)
	{
		*dif = rawtime - flags->atimes[i];
		*tmp = ctime(&flags->atimes[i]);
	}
	if (flags->ul)
	{
		*dif = rawtime - flags->ctimes[i];
		*tmp = ctime(&flags->ctimes[i]);
	}
}

void	ft_parse_date(t_ls *flags, int i, t_date *date)
{
	char	*tmp;
	time_t	rawtime;
	time_t	dif;

	time(&rawtime);
	dif = rawtime - flags->times[i];
	tmp = ctime(&flags->times[i]);
	ft_bonus_time(&dif, i, &tmp, flags);
	date->month[0] = tmp[4];
	date->month[1] = tmp[5];
	date->month[2] = tmp[6];
	date->month[3] = 0;
	date->day[0] = tmp[8];
	date->day[1] = tmp[9];
	date->day[2] = 0;
	if (dif > 25337076480 || dif < -25337076480)
		ft_get_year_f(date, tmp);
	else if (dif > 16070400 || dif < -16070400)
		ft_get_year(date, tmp);
	else
		ft_get_time(date, tmp);
}
