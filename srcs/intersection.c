/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:10:08 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 18:05:41 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		calc_co(double xa, double ya, t_intersection *a, t_win_info w)
{
	a->n_mob = 0;
	while (((int)(a->x / BLOC) < 32 && (int)(a->x / BLOC) > 0) &&
		(int)(a->y / BLOC) < 32 && (int)(a->y / BLOC) > 0)
	{
		if (w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == MONSTER ||
		w.map[(int)(a->y / BLOC)][(int)(a->x / BLOC)] == MONSTER + 1)
			a->n_mob++;
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

int				raycasting(t_win_info w, int id)
{
	pthread_t	ray_thread[8];
	int			i;

	i = 0;
	file_image(&w);
	pthread_create(&ray_thread[0], NULL, thread1, &w);
	pthread_create(&ray_thread[1], NULL, thread2, &w);
	pthread_create(&ray_thread[2], NULL, thread3, &w);
	pthread_create(&ray_thread[3], NULL, thread4, &w);
	pthread_create(&ray_thread[4], NULL, thread5, &w);
	pthread_create(&ray_thread[5], NULL, thread6, &w);
	pthread_create(&ray_thread[6], NULL, thread7, &w);
	pthread_create(&ray_thread[7], NULL, thread8, &w);
	while (i < 8)
	{
		pthread_join(ray_thread[i], NULL);
		i++;
	}
	hud(&w);
	put_sprite_wep(&w, id);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	image_hud(&w);
	return (0);
}
