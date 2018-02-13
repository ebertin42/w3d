/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:54:25 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/13 19:07:36 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	menu_bombe(t_win_info w, int x, int y, int token)
{
	if (token == 0)
		mlx_put_image_to_window(w.mlx, w.win, w.m.menu, 0, 0);
	else if (token == 1)
		mlx_put_image_to_window(w.mlx, w.win, w.m.settings, 0, 0);
	else if (token == 2)
		mlx_put_image_to_window(w.mlx, w.win, w.m.gameover, 0, 0);
	mlx_put_image_to_window(w.mlx, w.win, w.m.bombe, x, y);
}

void	new_game(t_win_info *w)
{
	t_line *data;

	data = read_data(w->str);
	check_good_nbdata(data);
	translate(data, w);
	init_data(w, 42);
}

void	message_change(t_win_info *w)
{
	mlx_string_put(w->mlx, w->win, 10, 140, 0xEEEEEE, "Choose your new key");
	mlx_string_put(w->mlx, w->win, 10, 160, 0xEEEEEE, "by pressing it.");
	w->m.change = 2;
}

void	game_over(t_win_info *w, int key)
{
	if (key == 125 || key == 126)
		w->m.go = w->m.go == 1 ? 0 : 1;
	if (w->m.go == 0)
		menu_bombe(*w, 97, 217, 2);
	else
		menu_bombe(*w, 227, 322, 2);
	if (key == 36)
	{
		if (w->m.go == 1)
		{
			w->m.statut = 0;
			menu_bombe(*w, 160, 170, 0);
		}
		else
		{
			w->m.statut = 1;
			w->player.life = 100;
			raycasting(*w, 4);
		}
	}
}
