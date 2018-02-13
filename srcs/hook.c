/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:18:46 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/13 15:02:38 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		ft_close(int keycode, void *param)
{
	t_win_info	*w;

	w = (t_win_info*)param;
	(void)keycode;
	kill(w->pid, SIGKILL);
	system("pkill afplay");
	exit(EXIT_SUCCESS);
	return (0);
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
	{
		if (cos(angle) > 0)
			w->player.pos_x += speed * fabs(cos(angle));
		else if (cos(angle) < 0)
			w->player.pos_x += -1 * (speed * fabs(cos(angle)));
		if (sin(angle) > 0)
			w->player.pos_y += -1 * (speed * fabs(sin(angle)));
		else if (sin(angle) < 0)
			w->player.pos_y += speed * fabs(sin(angle));
	}
	else if (keycode == w->player.backward)
	{
		if (cos(angle) > 0)
			w->player.pos_x -= speed * fabs(cos(angle));
		else if (cos(angle) < 0)
			w->player.pos_x -= -1 * (speed * fabs(cos(angle)));
		if (sin(angle) > 0)
			w->player.pos_y -= -1 * (speed * fabs(sin(angle)));
		else if (sin(angle) < 0)
			w->player.pos_y -= speed * fabs(sin(angle));
	}
	if (w->map[((int)(w->player.pos_y) / (int)BLOC)][((int)(w->player.pos_x) / (int)BLOC)] == WALL)
	{
		w->player.pos_x = tmp_x;
		w->player.pos_y = tmp_y;
	}
}


int		key_hook(int key, void *param)
{
	t_win_info			*w;
	t_intersection		a;
	t_intersection		b;
	int					token;
	static int			mob_v = 0;
	w = (t_win_info*)param;
	if(w->m.statut == 1 && key == 51)
		w->m.statut = 0;
	if(w->m.statut == 0)
		menu(key, w);
	if (key == KEY_ESC)
		ft_close(key, param);
	if(w->m.statut == 1)
	{
	if (key == w->player.left)
		w->player.dir_x += 5;
	if (key == w->player.right)
		w->player.dir_x -= 5;
	if (key == w->player.forward || key == w->player.backward)
		deplacement(w, key);
	if (key == SPRINT)
		w->player.sprint = w->player.sprint ^ 1;
	if (key == 15 && w->player.ammo != 8)
	{
		w->player.ammo = 8;
		system("afplay ./sounds/reload.mp3 -v 20 &");
	}
	if (key == 49)
	{
		w->id++;
		w->id = w->id > 6 ? 4 : w->id;
		if (w->player.ammo == 0)
			w->id = 4;
		a = find_intersection_ver(w->player.dir_x, *w, MONSTER);
		b = find_intersection_hor(w->player.dir_x, *w, MONSTER);
		a.dist = sqrt(pow((w->player.pos_x - a.x), 2) + pow((w->player.pos_y - a.y), 2));
		b.dist = sqrt(pow((w->player.pos_x - a.x), 2) + pow((w->player.pos_y - a.y), 2));
		token = a.dist > b.dist ? b.token : a.token;
		if (token == 1)
		{
			a.x = a.dist > b.dist ? b.x : a.x;
			a.x /= BLOC;
			a.y = a.dist > b.dist ? b.y : a.y;
			a.y /= BLOC;
			w->map[(int)a.y][(int)a.x] = 0;
		}
	}
	if (w->map[(int)w->player.pos_y / (int)BLOC][(int)w->player.pos_x / (int)BLOC] == MONSTER)
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
		}
	}
	raycasting(*w, w->id);
	}
	return (0);
}

