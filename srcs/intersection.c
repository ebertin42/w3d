/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:10:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/08 18:36:48 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_color(int y, int h_wall, int column, t_win_info w, int texid)
{
	int color;

	y = ((double)y / (double)h_wall) * BLOC;
	color = w.tex[texid].str[(column * 4) + ((int)BLOC * 4 * y)];
	color += w.tex[texid].str[(column * 4) + ((int)BLOC * 4 * y) + 1] * 256;
	color += (w.tex[texid].str[(column * 4) + ((int)BLOC * 4 * y) + 2] * 256) * 256;
	return (color);
}

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

void	draw(int x, int h_wall, t_win_info *w, int column, int texid)
{
	int y;
	int yim;

	y = SIZE_Y / 2 - h_wall / 2;
	yim = 0;
	if (y < 0)
	{
		yim -= y;
		y = 0;
	}
	while (y < SIZE_Y / 2 + h_wall / 2 && y < SIZE_Y - 1)
	{
		if (y < SIZE_Y && y >= 0)
			put_pixel_image(x, y, get_color(yim, h_wall, column, *w, texid), w);
		yim++;
		y++;
	}
	while (y < SIZE_Y - 1)
	{
		put_pixel_image(x, SIZE_Y - y, 0x808080, w);
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
	int				texid;

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
		beta = alpha > w.player.dir_x ? 30 : -30;
		dist = pa > pb ? pb : pa;
		h_wall = BLOC / dist * w.dist_player_proj;
		texid = 0;
		draw(x, h_wall, &w, pa > pb ? (int)b.y % (int)BLOC : (int)a.x % (int)BLOC, texid);
		x++;
	}
	hud(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	image_hud(&w);
	return (0);
}
