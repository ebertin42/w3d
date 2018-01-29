/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:07:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/29 18:29:33 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static double	alpha_inc(double alpha, t_win_info w)
{
	double nalpha;

	nalpha = alpha - (w.player.fov / (double)SIZE_X);
	if (nalpha <= 0)
		nalpha += 360;
	return (nalpha);
}

t_intersection	find_intersection_hor(double alpha, t_win_info w)
{
	t_intersection a;
	double	xa;
	double	ya;

	if (alpha >= 0 && alpha < 180)
	{
		a.y = (int)(w.player.pos_y / w.s_wall) * w.s_wall - 1);
		ya = -w.s_wall;
	}
	else
	{
		a.y = (int)(w.player.pos_y / w.s_wall) * w.s_wall + w.s_wall);
		ya = w.s_wall;
	}
	a.x = w.player.pos_x + (w.player.pos_y  - a.y) / tan(alpha);
	xa = w.s_wall / tan(alpha);
	while (1)
	{
		if (w.map[(int)(a.y / 64)][(int)(a.x / 64)] == 1)
			return (a);
		a.x = a.x + xa;
		a.y = a.y + ya;
	}
	return (NULL);
}

t_intersection	find_intersection_ver(double alpha, t_win_info w)
{
	t_intersection a;
	double	xa;
	double	ya;
	int		flag;

	flag = 0;
	if ((alpha <= 90 && alpha > 0) || (alpha >= 210 && alpha <= 360))
	{
		a.x = (int)(w.player.pos_x / w.s_wall) * w.s_wall + w.s_wall);
		xa = w.s_wall;
	}
	else
	{
		a.x = (int)(w.player.pos_x / w.s_wall) * w.s_wall - 1);
		xa = -w.s_wall;
	}
	a.y = w.player.pos_y + (w.player.pos_x  - a.x) / tan(alpha);
	ya = w.s_wall * tan(alpha);
	while (!flag)
	{
		if (w.map[(int)(a.y / w.s_wall)][(int)(a.x / w.s_wall)] == 1)
			return (a);
		a.x = a.x + xa;
		a.y = a.y + ya;
	}
	return (NULL);
}

int get_dist(t_win_info w)
{
	t_intersection a;
	t_intersection b;
	double		pa;
	double		pb;
	double	alpha;
	double	alpha_fin;

	alpha = w.player.dir_x + (w.player.fov / 2);
	alpha_fin = w.player.dir_x - (w.player.fov / 2);
	if (alpha > 360)
		alpha -= 360;
	if (alpha_fin <= 0)
		alpha_fin += 360;
	while (alpha != alpha_fin)
	{
		a = find_intersection_hor(alpha, w);
		b = find_intersection_ver(alpha, w);
		pa = abs()
		alpha = alpha_inc(alpha, w);
	}
}
