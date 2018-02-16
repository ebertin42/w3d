/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obstacle_detect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:06:04 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 11:53:43 by fde-souz         ###   ########.fr       */
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
	ob->n_mob = r.a.dist > r.b.dist ? r.b.n_mob : r.a.n_mob;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC :
														(int)r.a.x % (int)BLOC;
	return (1);
}

int						mob_detection(t_obstacle *ob, t_win_info w,
	double alpha, int state)
{
	t_raycasting r;

	r.a = sin(alpha * RAD) ? find_intersection_hor(alpha, w, state) : set(&r.a);
	r.b = cos(alpha * RAD) ? find_intersection_ver(alpha, w, state) : set(&r.b);
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
	ob->texid = state;
	ob->h = BLOC / ob->dist * w.dist_player_proj;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC :
														(int)r.a.x % (int)BLOC;
	ob->token = r.a.dist > r.b.dist ? r.b.token : r.a.token;
	return (0);
}
