/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:03:15 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/05 18:53:11 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	translate(t_line *data, t_win_info *w)
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
				if(w->map[y][x + 1] != 0 || w->map[y][x - 1] != 0 || w->map[y + 1][x] != 0 || w->map[y - 1][x] != 0)
					exit(0);
				else 
					break ;
			}
			x++;
		}
		y++;
	}
	if (flag_start != 1)
		return (0);
	return (1);
}
