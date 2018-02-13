/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:52:19 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/13 17:53:25 by vgauther         ###   ########.fr       */
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

void	sprite_menu(t_win_info *w, int token)
{
	if (token == 0)
	{
		if (w->m.set == 0)
			menu_bombe(*w, 575, 167, 1);
		else if (w->m.set == 1)
			menu_bombe(*w, 575, 232, 1);
		else if (w->m.set == 2)
			menu_bombe(*w, 575, 343, 1);
		else if (w->m.set == 3)
			menu_bombe(*w, 575, 408, 1);
	}
	else if (token == 1)
	{
		if (w->m.link == 0)
			menu_bombe(*w, 160, 170, 0);
		else if (w->m.link == 1)
			menu_bombe(*w, 180, 245, 0);
		else if (w->m.link == 2)
			menu_bombe(*w, 180, 315, 0);
		else
			menu_bombe(*w, 170, 415, 0);
	}
}

void	change_key(t_win_info *w, int key)
{
			if (w->m.set == 0)
				w->player.forward = key;
			else if (w->m.set == 1)
				w->player.backward = key;
			else if (w->m.set == 2)
				w->player.left = key;
			else if (w->m.set == 3)
				w->player.right = key;
			sprite_menu(w, 0);
			mlx_string_put(w->mlx, w->win, 10, 150, 0x00FF00, "Change saved.");
			w->m.change = 0;
}

void	ft_settings(t_win_info *w, int key)
{
	if (key == DEL && w->m.link == 2)
	{
		w->m.link = 0;
		menu_bombe(*w, 160, 170, 0);
		w->m.token_set = 0;
	}
	else
	{
		if (key == 36)
		{
			mlx_string_put(w->mlx, w->win, 10, 140, 0xEEEEEE, "Choose your new key");
			mlx_string_put(w->mlx, w->win, 10, 160, 0xEEEEEE, "by pressing it.");
			w->m.change = 2;
		}
		if (w->m.change == 1)
			change_key(w, key);
		else if (key != 36)
		{
			if (key == 126)
			{
				w->m.set--;
				if (w->m.set < 0)
					w->m.set = 3;
			}
			if (key == 125)
			{
				w->m.set++;
				if (w->m.set > 3)
					w->m.set = 0;
			}
			sprite_menu(w, 0);
		}
	}
	w->m.change = w->m.change == 2 ? 1 : 0;
}

int		menu(int key, t_win_info *w)
{
	t_line *data;

	if(w->m.statut == 42)
	{
		game_over(w, key);
	}
	else
	{
	if (w->m.token_set == 0)
	{
		if (key == 126)
		{
			w->m.link--;
			if (w->m.link < 0)
				w->m.link = 3;
		}
		if (key == 125)
		{
			w->m.link++;
			if (w->m.link > 3)
				w->m.link = 0;
		}
		if (key == DEL && w->m.link == 2)
		{
			w->m.link = 1;
			mlx_put_image_to_window(w->mlx, w->win, w->m.menu, 0, 0);
		}
		sprite_menu(w, 1);
		if (key == 8)
			mlx_put_image_to_window(w->mlx, w->win, w->m.credits, 0, 0);
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
				ft_close(key, w);
		}
	}
	else
		ft_settings(w, key);
	}
	return (0);
}

