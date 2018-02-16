/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:26:32 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 11:12:42 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	child(void)
{
	system("afplay ./sounds/8bit.mp3 &");
	exit(EXIT_SUCCESS);
}

void	start_child(t_win_info *w)
{
	w->pid = fork();
	if (w->pid == 0)
		child();
}

void	player_init(t_win_info *w)
{
	w->player.sprint = 1;
	w->player.life = 100;
	w->player.dir_x = 0;
	w->player.ammo = 8;
}
