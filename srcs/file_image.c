/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:34:34 by ebertin           #+#    #+#             */
/*   Updated: 2018/02/12 17:29:17 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	file_image(t_win_info *w)
{
	unsigned int	color;
	double			x;
	double			y;
	t_color			c;

	y = 0;
	color = 0;
	while (y < SIZE_Y / 2)
	{
		x = 0;
		while (x < SIZE_X)
		{
			c.b = w->sky.str[(int)((x * 4) + (y * w->sky.s))];
			c.g = w->sky.str[(int)((x * 4) + (y * w->sky.s)) + 1];
			c.r = w->sky.str[(int)((x * 4) + (y * w->sky.s)) + 2];
			color = c.b + c.g * 256 + (c.r * 256) * 256;
			put_pixel_image(x, y, color, w);
			x++;
		}
		y++;
	}
}
