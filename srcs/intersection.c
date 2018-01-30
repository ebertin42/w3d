/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:07:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/30 17:42:55 by fde-souz         ###   ########.fr       */
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

static double	calc_dist(double alpha, t_win_info w, double dist)
{
	double beta_min;
	double beta_max;
	double beta;
	int		token;

	beta = w.player.dir_x - 30;
	beta_max = w.player.dir_x + 30;
	if (beta_min < 0)
	{
		token = 1;
		beta_min += 360;
	}
	if (beta_max > 360)
	{
		token = 2;
		beta_max -= 360;
	}
	if (token == 1)

	else if(token == 2)

	else
	{
	if (alpha > w.player.dir_x && alpha < beta_max)
		beta = beta_max;
	else
		beta = beta_min;
	}

}

t_intersection	find_intersection_hor(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (alpha > 0.00 && alpha < 180.00)
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
	xa = 64 / tan(alpha * RAD);
	if ((int)(a.x / 64) < 32 && (int)(a.y / 64) < 32 && (int)(a.x / 64) > 0 && (int)(a.x / 64) > 0)
	{
		while (w.map[(int)(a.y / 64)][(int)(a.x / 64)] != WALL)
		{
			a.x += xa;
			a.y += ya;
			if (((int)(a.y / 64) > 32 || (int)(a.y / 64) < 0) || ((int)(a.x / 64) > 32 || (int)(a.x / 64) < 0))
			return (a);
		}
	}
	return (a);
}


t_intersection	find_intersection_ver(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (alpha > 90 && alpha < 210)
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC - 1;
		xa = -BLOC;
	}
	else
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC + BLOC;
		xa = BLOC;
	}
	a.y = w.player.pos_y + (w.player.pos_x - a.x) * tan(alpha * RAD);
	ya = 64 * tan(alpha * RAD);
	if ((int)(a.x / 64) < 32 && (int)(a.y / 64) < 32 && (int)(a.x / 64) > 0 && (int)(a.x / 64) > 0)
	{
		while (w.map[(int)(a.y / 64)][(int)(a.x / 64)] != WALL)
		{
			a.x += xa;
			a.y += ya;
			if (((int)(a.y / 64) > 32 || (int)(a.y / 64) < 0) || ((int)(a.x / 64) > 32 || (int)(a.x / 64) < 0))
				return (a);
		}
	}
	return (a);
}

int get_dist(t_win_info w)
{
	t_intersection a;
	t_intersection b;
	double		pa;
	double		pb;
	double		alpha;
	double		alpha_fin;
	double		h_wall;
	double		dist;

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
		pa = fabs(w.player.pos_x - a.x) / cos(alpha * RAD);
		pb = fabs(w.player.pos_x - b.x) / cos(alpha * RAD);
		dist = pa > pb ? pb : pa;
		if (alpha <= )
		printf("%f\n", dist);
		alpha = alpha_inc(alpha, w);
	}
	return (0);
}
