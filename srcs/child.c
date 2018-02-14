/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebertin <ebertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:26:32 by ebertin           #+#    #+#             */
/*   Updated: 2018/02/14 14:02:14 by ebertin          ###   ########.fr       */
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
