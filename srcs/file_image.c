/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:34:34 by ebertin           #+#    #+#             */
/*   Updated: 2018/02/12 13:32:21 by ebertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	file_image(t_win_info *w)
{
	unsigned int color;
	double			x;
	double			y;
	int				r;
	int				g;
	int				b;

	y = 0;
	color = 0;
	while (y < SIZE_Y / 2)
	{
		x = 0;
		while (x < SIZE_X)
		{
			b = w->sky.str[(int)((x * 4) + (y * w->sky.s))];
			g = w->sky.str[(int)((x* 4) + (y * w->sky.s)) + 1];
			r = w->sky.str[(int)((x * 4) + (y* w->sky.s)) + 2];
			color = b + g * 256 + (r * 256) * 256;
			put_pixel_image(x, y, color, w);
			x++;
		}
		y++;
	}
}
