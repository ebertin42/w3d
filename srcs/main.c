/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:43:01 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/12 17:24:05 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	put_sprite_wep(t_win_info *w, int texid)
{
	unsigned int	color;
	double			x;
	double			y;

	y = 0;
	color = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			color = w->tex[texid].str[(((int)(x / SIZE_X * 128) * 4) +
			((int)(y / SIZE_Y * 128) * w->tex[texid].s))] +
			w->tex[texid].str[(((int)(x / SIZE_X * 128) * 4) +
			((int)(y / SIZE_Y * 128) * w->tex[texid].s)) + 1] * 256 +
			(w->tex[texid].str[(((int)(x / SIZE_X * 128) * 4) +
			((int)(y / SIZE_Y * 128) * w->tex[texid].s)) + 2] * 256) * 256;
			if (color != 4288151432)
				put_pixel_image(x, y, color, w);
			x++;
		}
		y++;
	}
}

void	init_data(t_win_info *w)
{
	int a;
	int b;

	w->player.sprint = 0;
	w->player.life = 100;
	w->player.dir_x = 0;
	w->id = 4;
	w->player.dir_y = 0;
	w->player.pos_x = w->player.start_x;
	w->player.pos_y = w->player.start_y;
	w->player.fov = 60;
	w->dist_player_proj = (SIZE_X / 2) / tan((w->player.fov / 2) * RAD);
	w->img.img = mlx_xpm_file_to_image(w->mlx, "./assets/1.xpm", &a, &b);
	w->img.str = mlx_get_data_addr(w->img.img, &w->img.b, &w->img.s, &w->img.e);
	w->sky.img = mlx_xpm_file_to_image(w->mlx, "./assets/1.xpm", &a, &b);
	w->sky.str = mlx_get_data_addr(w->sky.img, &w->sky.b, &w->sky.s, &w->sky.e);
	w->pid = fork();
	if (w->pid == 0)
		child();
}

int		key_release(int key, void *param)
{
	t_win_info *w;

	w = (t_win_info*)param;
	if (key == 49)
	{
		system("afplay ./sounds/explode.wav &");
		w->id = 4;
		raycasting(*w, 4);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_line		*data;
	t_win_info	w;

	if (ac != 2)
		return (0);
	data = read_data(av[1]);
	check_good_nbdata(data);
	translate(data, &w);
	ennemies_place(w.map);
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, SIZE_X, SIZE_Y, "Wolf 3D");
	init_data(&w);
	load_texture_mur(&w);
	load_texture_sprite(&w);
	raycasting(w, 4);
	mlx_hook(w.win, 17, 0, ft_close, &w);
	mlx_hook(w.win, 2, 0, key_hook, &w);
	mlx_hook(w.win, 3, 0, key_release, &w);
	mlx_loop(w.mlx);
	return (0);
}
