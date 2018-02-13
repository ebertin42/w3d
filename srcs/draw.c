/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:43:02 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/13 16:16:08 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		get_color(int y, t_win_info w, t_obstacle ob)
{
	int color;

	y = ((double)y / (double)ob.h) * BLOC;
	color = w.tex[ob.texid].str[(ob.col * 4) + ((int)BLOC * 4 * y)];
	color += w.tex[ob.texid].str[(ob.col * 4) + ((int)BLOC * 4 * y) + 1] * 256;
	color += (w.tex[ob.texid].str[(ob.col * 4) + ((int)BLOC * 4 * y) + 2] *
			256) * 256;
	return (color);
}

void	draw(int x, t_win_info *w, t_obstacle ob)
{
	int y;
	int yim;
	unsigned int color;

	y = SIZE_Y / 2 - ob.h / 2;
	yim = 0;
	if (y < 0)
	{
		yim -= y;
		y = 0;
	}
	while (y < SIZE_Y / 2 + ob.h / 2 && y < SIZE_Y - 1)
	{
		if (y < SIZE_Y && y >= 0)
		{
			color = get_color(yim, *w, ob);
			if (color != 4288151431)
				put_pixel_image(x, y, color, w);
		}
		yim++;
		y++;
	}
	y--;
	while (++y < SIZE_Y)
		put_pixel_image(x, y, 0x808080, w);
}
