/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:43:01 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/13 15:30:54 by ebertin          ###   ########.fr       */
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

void	init_data(t_win_info *w, int token)
{
	int a;
	int b;

	if (token == 1)
	{
	w->player.left = LEFT;
	w->player.right = RIGHT;
	w->player.backward = BACKWARD;
	w->player.forward = FORWARD;
	}
	w->player.sprint = 0;
	w->player.life = 100;
	w->player.dir_x = 0;
	w->player.ammo = 8;
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
	t_win_info	*w;

	w = (t_win_info*)param;
	if (key == 49 && w->m.statut == 1)
	{
		w->id = 4;
		raycasting(*w, 4);
	}
	return (0);
}

int		menu(int key, t_win_info *w)
{
	t_line *data;

	if (w->m.token_set == 0)
	{
		if(key == 126)
		{
			w->m.link--;
			if (w->m.link < 0)
				w->m.link = 3;
		}
		if(key == 125)
		{
			w->m.link++;
			if (w->m.link > 3)
				w->m.link = 0;
		}
		if (key == 51 && w->m.link == 2)
		{
			w->m.link = 1;
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
		}
		if(w->m.link == 0)
		{
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
			mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 160, 170);
		}
		else if(w->m.link == 1)
		{
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
			mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 180, 245);
		}
		else if (w->m.link == 2)
		{
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
			mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 180, 315);
		}
		else
		{
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
			mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 170, 415);
		}
		if (key == 8)
		{
			mlx_put_image_to_window(w->mlx, w->win, w->m.credits, 0, 0);
		}
		if (key == 36)
		{
			if (w->m.link == 0 || w->m.link == 1)
			{
				w->m.statut = 1;
				if (w->m.link == 0)
				{
	data = read_data(w->str);
	check_good_nbdata(data);
	translate(data, w);

					init_data(w, 42);
			}
			}
			if (w->m.link == 2)
			{
				w->m.set = 0;
				w->m.token_set = 1;
				mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
				mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 167);
			}
			if (w->m.link == 3)
			{
				ft_close(key, w);
			}
		}
	}
	else
	{
		printf("%d\n", key);
		if (key == 51 && w->m.link == 2)
		{
			w->m.link = 0;
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
			mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 160, 170);
			w->m.token_set = 0;
		}
		else{
			if(key == 36)
			{
				mlx_string_put(w->mlx, w->win, 10, 140, 0xEEEEEE, "Choose your new key");
				mlx_string_put(w->mlx, w->win, 10, 160, 0xEEEEEE, "by pressing it.");
				w->m.change = 2;
			}
			if (w->m.change == 1)
			{
				if (w->m.set == 0)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 167);
					w->player.forward = key;
				}
				else if (w->m.set == 1)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 232);
					w->player.backward = key;
				}
				else if (w->m.set == 2)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 343);
					w->player.left = key;
				}
				else if (w->m.set == 3)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 408);
					w->player.right = key;
				}
				mlx_string_put(w->mlx, w->win, 10, 150, 0x00FF00, "Change saved.");
				w->m.change = 0;
			}
			else if (key != 36)
			{
				if(key == 126)
				{
					w->m.set--;
					if (w->m.set < 0)
						w->m.set = 3;
				}
				if(key == 125)
				{
					w->m.set++;
					if (w->m.set > 3)
						w->m.set = 0;
				}
				if (key == 51 && w->m.link == 2)
				{
					w->m.link = 1;
					mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
				}
				if(w->m.set == 0)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 167);
				}
				else if(w->m.set == 1)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 232);
				}
				else if (w->m.set == 2)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 343);
				}
				else if (w->m.set == 3)
				{
					mlx_put_image_to_window(w->mlx, w->win, w->m.settings, 0, 0);
					mlx_put_image_to_window(w->mlx, w->win, w->m.bombe, 575, 408);
				}
			}
		}
		if (w->m.change == 2)
			w->m.change = 1;
	}
	return (0);
}

void	init_menu(t_win_info *w)
{
	int a;
	int b;

	w->m.link = 0;
	w->m.statut = 0;
	w->m.token_set = 0;
	w->m.change = 0;
	w->m.menu = mlx_xpm_file_to_image(w->mlx, "assets/menu/menu.XPM", &a, &b);
	w->m.credits = mlx_xpm_file_to_image(w->mlx, "assets/menu/credits.XPM", &a, &b);
	w->m.settings = mlx_xpm_file_to_image(w->mlx, "assets/menu/settings.XPM", &a, &b);
	w->m.bombe = mlx_xpm_file_to_image(w->mlx, "assets/menu/bombe.XPM", &a, &b);
}

int		main(int ac, char **av)
{
	t_line		*data;
	t_win_info	w;

	if (ac != 2)
		return (0);
	w.str = av[1];
	data = read_data(av[1]);
	check_good_nbdata(data);
	translate(data, &w);
	ennemies_place(w.map);
	w.m.statut = 0;
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, SIZE_X, SIZE_Y, "Wolf 3D");
	init_data(&w, 1);
	init_menu(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.m.menu, 0, 0);
	mlx_put_image_to_window(w.mlx, w.win, w.m.bombe, 160, 170);
	load_texture_mur(&w);
	load_texture_sprite(&w);
	//raycasting(w, 4);
	//	mlx_hook(w.win, 4, 0, menu, &w);
	mlx_hook(w.win, 17, 0, ft_close, &w);
	mlx_hook(w.win, 2, 0, key_hook, &w);
	mlx_hook(w.win, 3, 0, key_release, &w);
	mlx_loop(w.mlx);
	return (0);
}
