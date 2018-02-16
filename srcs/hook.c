/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:18:46 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 11:13:18 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	damage(t_win_info *w)
{
	static int mob_v = 0;

	if (w->map[(int)w->player.pos_y / IBLOC][(int)w->player.pos_x / IBLOC] \
			== MONSTER)
	{
		if (mob_v == 0)
			w->player.life -= 15;
		mob_v++;
		if (mob_v >= 3)
			mob_v = 0;
		if (w->player.life <= 0)
		{
			w->player.pos_x = w->player.start_x;
			w->player.pos_y = w->player.start_y;
			w->player.life = 100;
			menu_bombe(*w, 160, 170, 0);
			w->m.statut = 42;
		}
	}
	if (w->m.statut == 1)
		raycasting(*w, w->id);
}

void	deplacement(t_win_info *w, int keycode)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;
	int		speed;

	angle = w->player.dir_x * RAD;
	tmp_x = w->player.pos_x;
	tmp_y = w->player.pos_y;
	if (w->player.sprint == 1)
		speed = 20;
	else
		speed = 45;
	if (keycode == w->player.forward)
		forward(w, angle, speed);
	else if (keycode == w->player.backward)
		backward(w, angle, speed);
	if (w->map[((int)(w->player.pos_y) / IBLOC)][((int)(w->player.pos_x) /
				IBLOC)] == WALL)
	{
		w->player.pos_x = tmp_x;
		w->player.pos_y = tmp_y;
	}
	damage(w);
}

void	init_mob_ray(t_hit_mob *v, t_win_info *w)
{
	v->a = find_intersection_ver(w->player.dir_x, *w, MONSTER);
	v->b = find_intersection_hor(w->player.dir_x, *w, MONSTER);
	v->a.dist = sqrt(pow((w->player.pos_x - v->a.x), 2) + pow((w->player.pos_y -
					v->a.y), 2));
	v->b.dist = sqrt(pow((w->player.pos_x - v->a.x), 2) + pow((w->player.pos_y -
					v->a.y), 2));
	v->token = v->a.dist > v->b.dist ? v->b.token : v->a.token;
}

void	hit_mob(t_win_info *w)
{
	t_hit_mob	v;

	w->id = (w->id + 1) > 6 ? 4 : (w->id + 1);
	if (w->player.ammo == 0)
	{
		system("afplay ./sounds/click.wav &");
		w->id = 4;
	}
	else
	{
		w->player.ammo--;
		system("afplay ./sounds/explode.wav &");
	}
	init_mob_ray(&v, w);
	if (v.token == 1)
	{
		v.a.x = v.a.dist > v.b.dist ? v.b.x / BLOC : v.a.x / BLOC;
		v.a.y = v.a.dist > v.b.dist ? v.b.y / BLOC : v.a.y / BLOC;
		w->map[(int)v.a.y][(int)v.a.x] = 8;
	}
}

int		key_hook(int key, void *param)
{
	t_win_info			*w;

	w = (t_win_info*)param;
	if (w->m.statut == 1 && key == 51)
		w->m.statut = 0;
	if (w->m.statut == 0 || w->m.statut == 42)
		menu(key, w);
	if (key == KEY_ESC)
		ft_close(key, param);
	if (w->m.statut == 1)
	{
		ft_moove(w, key);
		if (key == 15 && w->player.ammo != 8)
		{
			w->player.ammo = 8;
			system("afplay ./sounds/reload.mp3 -v 20 &");
		}
		if (key == 49)
			hit_mob(w);
		if (w->m.statut == 1)
			raycasting(*w, w->id);
	}
	return (0);
}
