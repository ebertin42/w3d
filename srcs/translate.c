/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:03:15 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/12 16:28:31 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	nowall(double map[32][32])
{
	int x;

	x = 0;
	while (x != 31)
	{
		if (map[0][x] != 1)
			map_error(1);
		else if (map[31][x] != 1)
			map_error(1);
		x++;
	}
	x = 0;
	while (x != 31)
	{
		if (map[x][0] != 1)
			map_error(1);
		else if (map[x][31] != 1)
			map_error(1);
		x++;
	}
}

void	ennemies_place(double tab[32][32])
{
	int x;
	int y;

	y = 0;
	while(y != 32)
	{
		x = 0;
		while(x != 32)
		{
			if(tab[y][x] == 7)
			{
				if(!((tab[y][x - 1] == 1 && tab[y][x + 1] == 1) || (tab[y - 1][x] == 1 && tab[y + 1][x] == 1)))
					map_error(4);
			}
			x++;
		}
		y++;
	}
}

int		translate(t_line *data, t_win_info *w)
{
	int x;
	int y;
	int flag_start;

	flag_start = 0;
	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			if (ft_atoi(data[y].line[x]) == 3)
			{
				flag_start++;
				w->player.start_x = x * BLOC;
				w->player.start_y = y * BLOC;
				w->map[y][x] = 3;
			}
			else
				w->map[y][x] = (double)ft_atoi(data[y].line[x]);
			x++;
		}
		y++;
	}
	y = 0;
	while (y != 32)
	{
		x = 0;
		while (x != 32)
		{
			if (w->map[y][x] == 3)
			{
				if (w->map[y][x + 1] != 0 || w->map[y][x - 1] != 0 ||
					w->map[y + 1][x] != 0 || w->map[y - 1][x] != 0)
					map_error(0);
				else
					break ;
			}
			x++;
		}
		y++;
	}
	nowall(w->map);
	if (flag_start != 1)
		return (0);
	return (1);
}
