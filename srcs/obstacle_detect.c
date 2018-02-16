/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obstacle_detect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:06:04 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 13:24:32 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_intersection	set(t_intersection *a)
{
	a->x = 10000;
	a->y = 10000;
	return (*a);
}

static void				get_texid(double alpha, t_obstacle *ob, t_raycasting r)
{
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
}

int						wall_detection(t_obstacle *ob,
		t_win_info w, double alpha)
{
	t_raycasting	r;

	r.a = sin(alpha * RAD) ? find_intersection_hor(alpha, w, WALL) : set(&r.a);
	r.b = cos(alpha * RAD) ? find_intersection_ver(alpha, w, WALL) : set(&r.b);
	r.a.dist = sqrt(pow((w.player.pos_x - r.a.x), 2) +
			pow((w.player.pos_y - r.a.y), 2));
	r.b.dist = sqrt(pow((w.player.pos_x - r.b.x), 2) +
			pow((w.player.pos_y - r.b.y), 2));
	if (r.a.dist > 0 && r.b.dist > 0)
		ob->dist = r.a.dist > r.b.dist ? r.b.dist : r.a.dist;
	else if (r.a.dist > 0)
		ob->dist = r.a.dist;
	else if (r.b.dist > 0)
		ob->dist = r.b.dist;
	get_texid(alpha, ob, r);
	ob->h = BLOC / ob->dist * w.dist_player_proj;
	ob->n_mob = r.a.n_mob < r.b.n_mob ? r.b.n_mob : r.a.n_mob;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC :
		(int)r.a.x % (int)BLOC;
	return (1);
}

static void calc_co_m(double xa, double ya, t_intersection *a, t_win_info w, int m)
{
	/*double x;
	 *	double y;*/
	int i;

	i = 0;
	a->token = 0;
	while (((int)(a->x / BLOC) < 32 && (int)(a->x / BLOC) > 0) &&
			(int)(a->y / BLOC) < 32 && (int)(a->y / BLOC) > 0)
	{
		if (w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == MONSTER || w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == MONSTER + 1)
		{
			a->token = 1;
			/*x = a->x;
			 *			y = a->y;*/
			i++;	
		}
		if (i == m)
		{
			/*a->x = x;
			 *			a->y = y;*/
			return ;
		}
		a->x += xa;
		a->y += ya;
	}
	/*a->x = x;
	 *	a->y = y;
	 *	*/}

t_intersection find_intersection_hor_m(double alpha, t_win_info w, int obstacle, int m)
{
	t_intersection a;
	double xa;
	double ya;

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
	calc_co_m(xa, ya, &a, w, m);
	return (a);
}

t_intersection find_intersection_ver_m(double alpha, t_win_info w, int obstacle, int m)
{
	t_intersection a;
	double xa;
	double ya;

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
	calc_co_m(xa, ya, &a, w, m);
	return (a);
}


int mob_detection(t_obstacle *ob, t_win_info w,
		double alpha, int state, int m)
{
	t_raycasting r;

	r.a = sin(alpha * RAD) ? find_intersection_hor_m(alpha, w, state, m) : set(&r.a);
	r.b = cos(alpha * RAD) ? find_intersection_ver_m(alpha, w, state, m) : set(&r.b);
	r.a.dist = sqrt(pow((w.player.pos_x - r.a.x), 2) +
			pow((w.player.pos_y - r.a.y), 2));
	r.b.dist = sqrt(pow((w.player.pos_x - r.b.x), 2) +
			pow((w.player.pos_y - r.b.y), 2));
	if (r.a.dist > 0 && r.b.dist > 0)
		ob->dist = r.a.dist > r.b.dist ? r.b.dist : r.a.dist;
	else if (r.a.dist > 0)
		ob->dist = r.a.dist;
	else if (r.b.dist > 0)
		ob->dist = r.b.dist;
	ob->texid = r.a.dist > r.b.dist ? w.map[(int)r.b.y / IBLOC][(int)r.b.x / IBLOC] : w.map[(int)r.a.y / IBLOC][(int)r.a.y];
	ob->h = BLOC / ob->dist * w.dist_player_proj;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC :
		(int)r.a.x % (int)BLOC;
	ob->token = r.a.dist > r.b.dist ? r.b.token : r.a.token;
	return (0);
}
