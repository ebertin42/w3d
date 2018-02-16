/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:28:18 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 11:14:06 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	forward(t_win_info *w, double angle, int speed)
{
	if (cos(angle) > 0)
		w->player.pos_x += speed * fabs(cos(angle));
	else if (cos(angle) < 0)
		w->player.pos_x += -1 * (speed * fabs(cos(angle)));
	if (sin(angle) > 0)
		w->player.pos_y += -1 * (speed * fabs(sin(angle)));
	else if (sin(angle) < 0)
		w->player.pos_y += speed * fabs(sin(angle));
}

void	backward(t_win_info *w, double angle, int speed)
{
	if (cos(angle) > 0)
		w->player.pos_x -= speed * fabs(cos(angle));
	else if (cos(angle) < 0)
		w->player.pos_x -= -1 * (speed * fabs(cos(angle)));
	if (sin(angle) > 0)
		w->player.pos_y -= -1 * (speed * fabs(sin(angle)));
	else if (sin(angle) < 0)
		w->player.pos_y -= speed * fabs(sin(angle));
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

int		ft_close(int keycode, void *param)
{
	t_win_info	*w;

	w = (t_win_info*)param;
	(void)keycode;
	kill(w->pid, SIGKILL);
	system("pkill afplay");
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_moove(t_win_info *w, int key)
{
	if (key == w->player.left)
		w->player.dir_x += 5;
	if (key == w->player.right)
		w->player.dir_x -= 5;
	if (key == w->player.forward || key == w->player.backward)
		deplacement(w, key);
	if (key == SPRINT)
		w->player.sprint = w->player.sprint ^ 1;
}
