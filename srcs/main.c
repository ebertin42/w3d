/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:43:01 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/29 17:09:35 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_data(t_win_info w)
{
	w->player.dir_x = 90;
	w->player.dir_y = 0;
	w->size_wall = 64;
	w->size_player = w->size_wall / 2;
	w->player.fov = 60;
}

int		main(int ac, char **av)
{
	t_line		*data;
	t_win_info	w;
	int			x;
	int			y;

	if (ac != 2)
		return (0);
	data = read_data(av[1]);
	printf("%d\n", check_good_nbdata(data));
	printf("%d\n", translate(data, &w));
	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			printf("%d ", (int)w.map[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
	printf("%d %d\n", w.player.start_x, w.player.start_y);
}
