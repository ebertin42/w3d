/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:10:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/13 08:07:45 by ebertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"



t_intersection find_intersection_hor(double alpha, t_win_info w, int obstacle)
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
	while (((int)(a.x / BLOC) < 32 && (int)(a.x / BLOC) > 0) && (int)(a.y / BLOC) < 32 && (int)(a.y / BLOC) > 0)
	{
		if (w.map[(int)(a.y / BLOC)][(int)(a.x / BLOC)] == obstacle)
		{
			a.token = 1;
			return (a);
		}
		a.x += xa;
		a.y += ya;
	}
	return (a);
}

t_intersection find_intersection_ver(double alpha, t_win_info w, int obstacle)
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
	while (((int)(a.x / BLOC) < 32 && (int)(a.x / BLOC) > 0) && (int)(a.y / BLOC) < 32 && (int)(a.y / BLOC) > 0)
	{
		if (w.map[(int)(a.y / BLOC)][(int)(a.x / BLOC)] == obstacle)
		{
			a.token = 1;
			return (a);
		}
		a.x += xa;
		a.y += ya;
	}
	return (a);
}


int		wall_detection(t_obstacle *ob, t_win_info w, double alpha)
{
	t_raycasting	r;

	r.a.x = 10000;
	r.a.y = 10000;
	r.b.x = 10000;
	r.b.y = 10000;
	r.a.dist = 10000;
	r.b.dist = 10000;
	if (sin(alpha * RAD))
		r.a = find_intersection_hor(alpha, w, WALL);
	if (cos(alpha * RAD))
		r.b = find_intersection_ver(alpha, w, WALL);
	r.a.dist = sqrt(pow((w.player.pos_x - r.a.x), 2) + pow((w.player.pos_y - r.a.y), 2));
	r.b.dist = sqrt(pow((w.player.pos_x - r.b.x), 2) + pow((w.player.pos_y - r.b.y), 2));
	if (r.a.dist > 0 && r.b.dist > 0)
		ob->dist = r.a.dist > r.b.dist ? r.b.dist : r.a.dist;
	else if (r.a.dist > 0)
		ob->dist = r.a.dist;
	else if (r.b.dist > 0)
		ob->dist = r.b.dist;
	if (ob->dist == r.b.dist)
	{
		if (cos(alpha * RAD) > 0)
			ob->texid = 0;
		else
			ob->texid = 1;
	}
	else
	{
		if (sin(alpha * RAD) > 0)
			ob->texid = 2;
		else
			ob->texid = 3;
	}
	ob->h = BLOC / ob->dist * w.dist_player_proj;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC : (int)r.a.x % (int)BLOC;
	return (1);
}

int		mob_detection(t_obstacle *ob, t_win_info w, double alpha)
{
	t_raycasting r;

	r.a.x = 10000;
	r.a.y = 10000;
	r.b.x = 10000;
	r.b.y = 10000;
	r.a.dist = 10000;
	r.b.dist = 10000;
	if (sin(alpha * RAD))
		r.a = find_intersection_hor(alpha, w, MONSTER);
	if (cos(alpha * RAD))
		r.b = find_intersection_ver(alpha, w, MONSTER);
	r.a.dist = sqrt(pow((w.player.pos_x - r.a.x), 2) + pow((w.player.pos_y - r.a.y), 2));
	r.b.dist = sqrt(pow((w.player.pos_x - r.b.x), 2) + pow((w.player.pos_y - r.b.y), 2));
	if (r.a.dist > 0 && r.b.dist > 0)
		ob->dist = r.a.dist > r.b.dist ? r.b.dist : r.a.dist;
	else if (r.a.dist > 0)
		ob->dist = r.a.dist;
	else if (r.b.dist > 0)
		ob->dist = r.b.dist;
	ob->texid = MONSTER;
	ob->h = BLOC / ob->dist * w.dist_player_proj;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC : (int)r.a.x % (int)BLOC;
	ob->token = r.a.dist > r.b.dist ? r.b.token : r.a.token;
	return (0);
}

int		raycasting(t_win_info w, int test)
{
	t_obstacle		ob;
	t_obstacle		ob_mob;
	double			alpha;
	int				x;

	file_image(&w);
	x = 0;
	while (x <= SIZE_X)
	{
		alpha = (w.player.dir_x + (w.player.fov / 2)) -
			((w.player.fov / SIZE_X) * x);
		wall_detection(&ob, w, alpha);
		mob_detection(&ob_mob, w, alpha);
		draw(x, &w, ob);
		if(ob_mob.token == 1 && ob.dist > ob_mob.dist)
			draw(x, &w, ob_mob);
		x++;
	}
	hud(&w);
	put_sprite_wep(&w, test);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	image_hud(&w);
	ammo(&w);
	return (0);
}
