/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:43:01 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/31 14:47:57 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_data(t_win_info *w)
{
	w->player.dir_x = 0;
	w->player.dir_y = 0;
	w->player.pos_x = w->player.start_x;
	w->player.pos_y = w->player.start_y;
	w->player.fov = 60;
	w->dist_player_proj = (SIZE_X / 2) / tan((w->player.fov / 2) * RAD);
	w->img.img = mlx_new_image(w->mlx, SIZE_X, SIZE_Y);
	w->img.str = mlx_get_data_addr(w->img.img, &w->img.b, &w->img.s, &w->img.e);
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
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, SIZE_X, SIZE_Y, "fractol");
	init_data(&w);
	raycasting(w);
	mlx_loop(w.mlx);
	return (0);
}
