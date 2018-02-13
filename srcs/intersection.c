/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:10:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/13 18:27:08 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		calc_co(double xa, double ya, t_intersection *a, t_win_info w)
{
	while (((int)(a->x / BLOC) < 32 && (int)(a->x / BLOC) > 0) &&
		(int)(a->y / BLOC) < 32 && (int)(a->y / BLOC) > 0)
	{
		if (w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == a->obstacle)
		{
			a->token = 1;
			return ;
		}
		a->x += xa;
		a->y += ya;
	}
}

t_intersection	find_intersection_hor(double alpha, t_win_info w, int obstacle)
{
	t_intersection	a;
	double			xa;
	double			ya;

	a.token = 0;
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
	a.obstacle = obstacle;
	calc_co(xa, ya, &a, w);
	return (a);
}

t_intersection	find_intersection_ver(double alpha, t_win_info w, int obstacle)
{
	t_intersection	a;
	double			xa;
	double			ya;

	a.token = 0;
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
	a.obstacle = obstacle;
	calc_co(xa, ya, &a, w);
	return (a);
}

int				raycasting(t_win_info w, int test)
{
	t_obstacle		ob;
	t_obstacle		ob_mob;
	t_obstacle		ob_mob_dead;
	double			alpha;
	int				x;

	file_image(&w);
	x = 0;
	while (x <= SIZE_X)
	{
		alpha = (w.player.dir_x + (w.player.fov / 2)) -
			((w.player.fov / SIZE_X) * x);
		wall_detection(&ob, w, alpha);
		mob_detection(&ob_mob, w, alpha, MONSTER);
		mob_detection(&ob_mob_dead, w, alpha, 8);
		draw(x, &w, ob);
		if (ob_mob.token == 1 && ob.dist > ob_mob.dist)
			draw(x, &w, ob_mob);
		if (ob_mob_dead.token == 1 && ob.dist > ob_mob_dead.dist)
			draw(x, &w, ob_mob_dead);
		x++;
	}
	hud(&w);
	put_sprite_wep(&w, test);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	image_hud(&w);
	return (0);
}
