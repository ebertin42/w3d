/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_detection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:55:38 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/16 19:05:02 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		calc_co_m(t_dec d, t_intersection *a,
		t_win_info w, int m)
{
	int i;

	i = 0;
	a->token = 0;
	while (((int)(a->x / BLOC) < 32 && (int)(a->x / BLOC) > 0) &&
			(int)(a->y / BLOC) < 32 && (int)(a->y / BLOC) > 0)
	{
		if (w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == MONSTER ||
				w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == MONSTER +
				w.deadornot)
		{
			a->token = 1;
			i++;
		}
		if (i == m)
			return ;
		a->x += d.xa;
		a->y += d.ya;
	}
}

t_intersection	find_intersection_hor_m(double alpha, t_win_info w, int m)
{
	t_intersection	a;
	t_dec			d;

	a.token = 0;
	if (sin(alpha * RAD) > 0)
	{
		a.y = (int)(w.player.pos_y / BLOC) * BLOC - 1;
		d.ya = -BLOC;
		d.xa = 1;
	}
	else
	{
		a.y = (int)(w.player.pos_y / BLOC) * BLOC + BLOC;
		d.ya = BLOC;
		d.xa = -1;
	}
	a.x = w.player.pos_x + (w.player.pos_y - a.y) / tan(alpha * RAD);
	d.xa *= BLOC / tan(alpha * RAD);
	calc_co_m(d, &a, w, m);
	return (a);
}

t_intersection	find_intersection_ver_m(double alpha, t_win_info w, int m)
{
	t_intersection	a;
	t_dec			d;

	a.token = 0;
	if (cos(alpha * RAD) > 0)
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC + BLOC;
		d.xa = BLOC;
		d.ya = -1;
	}
	else
	{
		a.x = (int)(w.player.pos_x / BLOC) * BLOC - 1;
		d.xa = -BLOC;
		d.ya = 1;
	}
	a.y = w.player.pos_y + (w.player.pos_x - a.x) * tan(alpha * RAD);
	d.ya *= BLOC * tan(alpha * RAD);
	calc_co_m(d, &a, w, m);
	return (a);
}

int				mob_detection(t_obstacle *ob, t_win_info w,
		double alpha, int m)
{
	t_raycasting	r;

	r.a = sin(alpha * RAD) ? find_intersection_hor_m(alpha, w, m) : set(&r.a);
	r.b = cos(alpha * RAD) ? find_intersection_ver_m(alpha, w, m) : set(&r.b);
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
	ob->texid = ob->dist == r.b.dist ? w.map[(int)r.b.y / IBLOC][(int)r.b.x /
		IBLOC] : w.map[(int)r.a.y / IBLOC][(int)r.a.x / IBLOC];
	ob->h = BLOC / ob->dist * w.dist_player_proj;
	ob->col = r.a.dist > r.b.dist ? (int)r.b.y % (int)BLOC :
		(int)r.a.x % (int)BLOC;
	ob->token = ob->dist == r.b.dist ? r.b.token : r.a.token;
	ob->x = ob->dist == r.b.dist ? (int)(r.b.x / BLOC) : (int)(r.a.x / BLOC);
	ob->y = ob->dist == r.b.dist ? (int)(r.b.y / BLOC) : (int)(r.a.y / BLOC);
	return (0);
}
