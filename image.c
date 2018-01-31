/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:38 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/15 16:11:47 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel_image(int x, int y, int color, t_win_info *wininf)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	wininf->str[(x * 4) + (wininf->sl * y)] = b;
	wininf->str[(x * 4) + (wininf->sl * y) + 1] = g;
	wininf->str[(x * 4) + (wininf->sl * y) + 2] = r;
	wininf->str[(x * 4) + (wininf->sl * y) + 3] = 0;
}
