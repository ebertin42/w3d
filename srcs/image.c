/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:38 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/05 11:11:21 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pixel_image(int x, int y, int color, t_win_info *w)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	w->img.str[(x * 4) + ((int)SIZE_X * 4 * y)] = b;
	w->img.str[(x * 4) + ((int)SIZE_X * 4 * y) + 1] = g;
	w->img.str[(x * 4) + ((int)SIZE_X * 4 * y) + 2] = r;
	w->img.str[(x * 4) + ((int)SIZE_X * 4 * y) + 3] = 0;
}
