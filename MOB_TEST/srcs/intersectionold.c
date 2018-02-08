/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:07:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/31 13:06:59 by fde-souz         ###   ########.fr       */
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

static double	calc_dist(double alpha, t_win_info w, double dist, double alpha_fin)
{
	while (alpha != alpha_fin)
	{
		if (alpha == w.player.dir_x)
			return (dist * cos(30 * RAD));
		alpha = alpha_inc(alpha, w);
	}
	return (dist * cos(-30 * RAD));
}

t_intersection	find_intersection_hor(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (alpha > 0.00 && alpha < 180)
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

	if (alpha > 90 && alpha < 270)
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

void			ft_draw(t_win_info *w, double h_wall, int x)
{
	int y;
	double stop;
	int stop2;

	stop2 = 0;
	stop = h_wall / 2.00;
	y = (int)SIZE_Y / 2;
	while ((double)stop2 < stop)
	{
		put_pixel_image(x, y, 0xFF0000, w);
		y++;
		stop2++;
	}
	y = (int)SIZE_Y / 2;
	stop2 = 0;
	while ((double)stop2 < stop)
	{
		put_pixel_image(x, y, 0xFF0000, w);
		stop2++;
		y--;
	}
}

int 			get_dist(t_win_info w)
{
	t_intersection	a;
	t_intersection	b;
	double			pa;
	double			pb;
	double			alpha;
	double			alpha_fin;
	double			h_wall;
	double			dist;
	int				x;

	x = 0;
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
		dist = calc_dist(alpha, w, dist, alpha_fin);
		h_wall = (BLOC / dist) * w.dist_player_proj;
		printf("%f %f\n", b.x, b.y);

		//ft_draw(&w, h_wall, x);
		alpha = alpha_inc(alpha, w);
		x++;
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	return (0);
}
