/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:43:01 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/08 18:04:54 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_data(t_win_info *w)
{
	w->player.sprint = 0;
	w->player.life = 100;
	w->player.dir_x = 0;
	w->player.dir_y = 0;
	w->player.pos_x = w->player.start_x;
	w->player.pos_y = w->player.start_y;
	w->player.fov = 60;
	w->dist_player_proj = (SIZE_X / 2) / tan((w->player.fov / 2) * RAD);
	w->img.img = mlx_new_image(w->mlx, SIZE_X, SIZE_Y);
	w->img.str = mlx_get_data_addr(w->img.img, &w->img.b, &w->img.s, &w->img.e);
}

void	deplacement(t_win_info *w, int keycode)
{
	double angle;
	double tmp_x;
	double tmp_y;
	int		speed;

	angle = w->player.dir_x * RAD;
	tmp_x = w->player.pos_x;
	tmp_y = w->player.pos_y;
	if (w->player.sprint == 1)
		speed = 20;
	else
		speed = 45;
	if (keycode == 13)
	{
		if(cos(angle) > 0)
			w->player.pos_x += speed * fabs(cos(angle));
		else if(cos(angle) < 0)
			w->player.pos_x += -1 * (speed * fabs(cos(angle)));
		if (sin(angle) > 0)
			w->player.pos_y += -1 * (speed * fabs(sin(angle)));
		else if (sin(angle) < 0)
			w->player.pos_y += speed * fabs(sin(angle));
	}
	else if (keycode == 1)
	{
		if(cos(angle) > 0)
			w->player.pos_x -= speed * fabs(cos(angle));
		else if(cos(angle) < 0)
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

int key_hook(int key, void *param)
{
	t_win_info *w;

	w = (t_win_info*)param;
	if (key == KEY_ESC)
		exit(0);
	if (key == 0)
		w->player.dir_x += 5;
	if (key == 2)
		w->player.dir_x -= 5;
	if (key == 1 || key == 13)
		deplacement(w, key);
	if (key == SPRINT)
	{
		if (w->player.sprint == 0)
			w->player.sprint = 1;
		else
			w->player.sprint = 0;
	}
	raycasting(*w);
	return(0);
}

int	ft_close(int keycode, void *param)
{
	(void)param;
	(void)keycode;
	exit(EXIT_SUCCESS);
	return (0);
}

int		main(int ac, char **av)
{
	t_line		*data;
	t_win_info	w;
	int			x;
	int			y;

	if (ac != 2)
		return (0);
	data = read_data(av[1]);
	printf("%d\n", check_good_nbdata(data));
	printf("%d\n", translate(data, &w));
	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			printf("%d ", (int)w.map[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, SIZE_X, SIZE_Y, "Wolf 3D");
	init_data(&w);
	printf("%d\n", load_texture(&w));
	raycasting(w);
	mlx_hook(w.win, 17, 0, ft_close, &w);
	mlx_hook(w.win, 2, 0, key_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}
