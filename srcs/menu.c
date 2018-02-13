/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:52:19 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/13 15:56:44 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

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

