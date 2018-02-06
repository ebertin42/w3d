/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:10:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/06 18:29:54 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_intersection find_intersection_hor(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (sin(alpha * RAD) > 0)
	{
		a.y = (int)(w.player.pos_y / BLOC) * BLOC - 1;
		ya = -BLOC;
		xa = 1;
	}
	else
	{
		a.y = (int)(w.player.pos_y / BLOC) * BLOC + BLOC;
		ya = BLOC;
		xa = -1;
	}
	a.x = w.player.pos_x + (w.player.pos_y - a.y) / tan(alpha * RAD);
	xa *= BLOC / tan(alpha * RAD);
	while (((int)(a.x / BLOC) < 32 && (int)(a.x / BLOC) > 0) && (int)(a.y / BLOC) < 32 && (int)(a.y / BLOC) > 0)
	{
		if (w.map[(int)(a.y / BLOC)][(int)(a.x / BLOC)] == WALL)
			return (a);
		a.x += xa;
		a.y += ya;
	}
	return (a);
}

t_intersection find_intersection_ver(double alpha, t_win_info w)
{
	t_intersection	a;
	double			xa;
	double			ya;

	if (cos(alpha * RAD) > 0)
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC + BLOC;
		xa = BLOC;
		ya = -1;
	}
	else
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC - 1;
		xa = -BLOC;
		ya = 1;
	}
	a.y = w.player.pos_y + (w.player.pos_x - a.x) * tan(alpha * RAD);
	ya *= BLOC * tan(alpha * RAD);
	while (((int)(a.x / BLOC) < 32 && (int)(a.x / BLOC) > 0) && (int)(a.y / BLOC) < 32 && (int)(a.y / BLOC) > 0)
	{
		if (w.map[(int)(a.y / BLOC)][(int)(a.x / BLOC)] == WALL)
			return (a);
		a.x += xa;
		a.y += ya;
	}
	return (a);
}

void	draw(int x, int h_wall, t_win_info *w)
{
	int y;

	y = SIZE_Y / 2 - h_wall / 2;
	while(y < SIZE_Y / 2 + h_wall / 2)
	{
		put_pixel_image(x, y, 0xff0000, w);
		y++;
	}
	while(y < SIZE_Y - 1)
	{
		put_pixel_image(x, y, 0x808080, w);
		y++;
	}
}

int		raycasting(t_win_info w)
{
	t_intersection	a;
	t_intersection	b;
	double			alpha;
	int				x;
	double			pa;
	double			pb;
	int				dist;
	int				beta;
	int				h_wall;

	x = 0;
	while (x <= SIZE_X)
	{
		alpha = (w.player.dir_x + (w.player.fov / 2)) - ((w.player.fov / SIZE_X) * x);
		a.x = 10000;
		a.y = 10000;
		b.x = 10000;
		b.y = 10000;
		pa = 10000;
		pb = 10000;
		if (sin(alpha * RAD))
			a = find_intersection_hor(alpha, w);
		if (cos(alpha * RAD))
			b = find_intersection_ver(alpha, w);
		pa = sqrt(powf((w.player.pos_x - a.x), 2) + powf((w.player.pos_y - a.y), 2));
		pb = sqrt(powf((w.player.pos_x - b.x), 2) + powf((w.player.pos_y - b.y), 2));
		beta = alpha > w.player.dir_x ? -30 : -30;
		dist = pa > pb ? pb * cos(beta * RAD) : pa * cos(beta * RAD);
		h_wall = dist < 10 ? SIZE_Y : BLOC / dist * w.dist_player_proj;
		h_wall = h_wall > SIZE_Y ? SIZE_Y - 1 : h_wall;
		draw(x, h_wall, &w);
		x++;
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	return (0);
}
