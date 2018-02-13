/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:54:25 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/13 18:11:49 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	game_over(t_win_info *w, int key)
{
	if (key == 126)
	{
		w->m.go--;
		if (w->m.go < 0)
			w->m.go = 1;
	}
	if (key == 125)
	{
		w->m.go++;
		if (w->m.go > 1)
			w->m.go = 0;
	}
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
