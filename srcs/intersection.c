/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:10:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/31 14:47:03 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_intersection find_intersection_hor(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (sin(alpha * RAD) == 0)
	{
		a.x = 10000;
		a.y = 10000;
		return (a);
	}
	else if (sin(alpha * RAD) > 0)
	{
		a.y = (int)(w.player.pos_y / BLOC) * BLOC - 1;
		ya = -BLOC;
	}
	else
	{
		a.y = (int)(w.player.pos_y / BLOC) * BLOC + BLOC;
		ya = BLOC;
	}
	a.x = w.player.pos_x + (w.player.pos_y - a.y) / tan(alpha * RAD);
	xa = BLOC / tan(alpha * RAD);
	while (w.map[(int)(a.y / 64)][(int)(a.x / 64)] != WALL)
	{
		a.x += xa;
		a.y += ya;
		if (a.x > 32 || a.x < 0 || a.y > 32 || a.y < 0)
			return (a);
	}
	return (a);
}

t_intersection find_intersection_ver(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (cos(alpha * RAD) == 0)
	{
		a.x = 10000;
		a.y = 10000;
		return (a);
	}
	else if (cos(alpha * RAD) > 0)
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC + BLOC;
		xa = BLOC;
	}
	else
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC - 1;
		xa = -BLOC;
	}
	a.y = w.player.pos_y + (w.player.pos_x - a.x) * tan(alpha * RAD);
	ya = BLOC * tan(alpha * RAD);
	if (!(a.x > 32 || a.x < 0 || a.y > 32 || a.y < 0))
	{
		while (w.map[(int)(a.y / 64)][(int)(a.x / 64)] != WALL)
		{
			a.x += xa;
			a.y += ya;
			if (a.x > 32 || a.x < 0 || a.y > 32 || a.y < 0)
				return (a);
		}
	}
	return (a);
}


int		raycasting(t_win_info w)
{
	t_intersection	a;
	t_intersection	b;
	double			alpha;
	double			alpha_fin;

	alpha = w.player.dir_x + (w.player.fov / 2);
	alpha_fin = w.player.dir_x - (w.player.fov / 2);
	while (alpha >= alpha_fin)
	{
		a = find_intersection_hor(alpha, w);
		b = find_intersection_ver(alpha, w);
		printf("a :%f %f %f\n", a.x / 64, a.y / 64, alpha);
		printf("b :%f %f %f\n", b.x / 64, b.y / 64, alpha);
		alpha -= w.player.fov / SIZE_X;
	}
	return (0);
}
