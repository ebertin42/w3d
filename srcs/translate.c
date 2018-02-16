/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:03:15 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 19:15:03 by fde-souz         ###   ########.fr       */
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

void		ennemies_place(double tab[32][32])
{
	int x;
	int y;

	y = 0;
	while (y != 32)
	{
		x = 0;
		while (x != 32)
		{
			if (tab[y][x] == 7)
			{
				if (!((tab[y][x - 1] == 1 && tab[y][x + 1] == 1) || \
							(tab[y - 1][x] == 1 && tab[y + 1][x] == 1)))
					map_error(4);
			}
			if (tab[y][x] == 1)
			{
				if (tab[y][x - 1] == 0 && tab[y][x + 1] == 0 && \
							tab[y - 1][x] == 0 && tab[y + 1][x] == 0)
					map_error(5);
			}
			x++;
		}
		y++;
	}
}

int			translate(t_line *data, t_win_info *w)
{
	t_coord		c;
	int			flag_start;

	flag_start = 0;
	c.y = 0;
	while (c.y < 32)
	{
		c.x = 0;
		while (c.x < 32)
		{
			if (ft_atoi(data[c.y].line[c.x]) == 3)
			{
				w->player.start_x = c.x * BLOC;
				w->player.start_y = c.y * BLOC;
				w->map[c.y][c.x] = 3;
				flag_start++;
			}
			else
				w->map[c.y][c.x] = (double)ft_atoi(data[c.y].line[c.x]);
			c.x++;
		}
		c.y++;
	}
	nowall(w->map);
	return (flag_start != 1 ? 0 : 1);
}
