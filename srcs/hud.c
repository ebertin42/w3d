/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 19:11:17 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/07 15:34:09 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	cursor2(t_win_info *w)
{
	put_pixel_image(SIZE_X / 2 - 3, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 - 4, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 - 5, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 - 6, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 + 3, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 + 4, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 + 5, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2 + 6, SIZE_Y / 2, 0xFFFFFF, w);

}

void	cursor(t_win_info *w)
{
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 + 3, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 + 4, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 + 5, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 + 6, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 - 3, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 - 4, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 - 5, 0xFFFFFF, w);
	put_pixel_image(SIZE_X / 2, SIZE_Y / 2 - 6, 0xFFFFFF, w);
	cursor2(w);
}

void	rectangle(t_rectangle r, t_win_info *w)
{	
	int x;
	int y;

	y = 0;
	while(y != r.hei)
	{
		x = 0;
		while(x != r.len)
		{
			put_pixel_image(r.x + x, r.y + y, r.color, w);
			x++;
		}
		y++;
	}
}

void	life_point(t_win_info *w)
{
	t_rectangle r;

	r.x = (SIZE_X / 2) + (SIZE_X / 4) + (SIZE_X/16);
	r.y = 15;
	r.len = w->player.life;
	r.hei = 10;
	r.color = 0x00FF00;
	rectangle(r, w);
}

void	hud(t_win_info *w)
{
	life_point(w);
	cursor(w);
}

void	image_hud(t_win_info *w)
{
	int hei;
	int len;
	void *h;

	h = mlx_xpm_file_to_image(w->mlx, "assets/h.xpm", &len, &hei);
	mlx_put_image_to_window(w->mlx, w->win, h,(SIZE_X / 2) + (SIZE_X / 4) + (SIZE_X/16) - 25 , 13);
}
