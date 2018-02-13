/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:28:18 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/13 16:31:51 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	forward(t_win_info *w, double angle, int speed)
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

void	backward(t_win_info *w, double angle, int speed)
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
