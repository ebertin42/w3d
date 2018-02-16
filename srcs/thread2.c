/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:07:19 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 18:10:48 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	*thread1(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 0;
	w = (t_win_info *)param;
	while (x < 90)
	{
		alpha = (w->player.dir_x + (w->player.fov / 2)) -
			((w->player.fov / SIZE_X) * x);
		wall_detection(&v.ob, *w, alpha);
		draw(x, w, v.ob);
		while (v.ob.n_mob != 0)
		{
			mob_detection(&v.ob_mob, *w, alpha, v.ob.n_mob);
			v.ob.dist > v.ob_mob.dist ? draw(x, w, v.ob_mob) : 0;
			v.ob.n_mob--;
		}
		x++;
	}
	return (NULL);
}

void	*thread2(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 90;
	w = (t_win_info *)param;
	while (x < 180)
	{
		alpha = (w->player.dir_x + (w->player.fov / 2)) -
			((w->player.fov / SIZE_X) * x);
		wall_detection(&v.ob, *w, alpha);
		draw(x, w, v.ob);
		while (v.ob.n_mob != 0)
		{
			mob_detection(&v.ob_mob, *w, alpha, v.ob.n_mob);
			v.ob.dist > v.ob_mob.dist ? draw(x, w, v.ob_mob) : 0;
			v.ob.n_mob--;
		}
		x++;
	}
	return (NULL);
}

void	*thread3(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 180;
	w = (t_win_info *)param;
	while (x <= 270)
	{
		alpha = (w->player.dir_x + (w->player.fov / 2)) -
			((w->player.fov / SIZE_X) * x);
		wall_detection(&v.ob, *w, alpha);
		draw(x, w, v.ob);
		while (v.ob.n_mob != 0)
		{
			mob_detection(&v.ob_mob, *w, alpha, v.ob.n_mob);
			v.ob.dist > v.ob_mob.dist ? draw(x, w, v.ob_mob) : 0;
			v.ob.n_mob--;
		}
		x++;
	}
	return (NULL);
}

void	*thread4(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 270;
	w = (t_win_info *)param;
	while (x < 360)
	{
		alpha = (w->player.dir_x + (w->player.fov / 2)) -
			((w->player.fov / SIZE_X) * x);
		wall_detection(&v.ob, *w, alpha);
		draw(x, w, v.ob);
		while (v.ob.n_mob != 0)
		{
			mob_detection(&v.ob_mob, *w, alpha, v.ob.n_mob);
			v.ob.dist > v.ob_mob.dist ? draw(x, w, v.ob_mob) : 0;
			v.ob.n_mob--;
		}
		x++;
	}
	return (NULL);
}
