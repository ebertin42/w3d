/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:57 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 18:11:04 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	*thread5(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 360;
	w = (t_win_info *)param;
	while (x < 450)
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

void	*thread6(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 450;
	w = (t_win_info *)param;
	while (x < 540)
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

void	*thread7(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 540;
	w = (t_win_info *)param;
	while (x <= 630)
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

void	*thread8(void *param)
{
	t_win_info		*w;
	t_all_ob		v;
	double			alpha;
	int				x;

	x = 630;
	w = (t_win_info *)param;
	while (x < 720)
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
