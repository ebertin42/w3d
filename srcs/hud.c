/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 19:11:17 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/06 19:22:12 by vgauther         ###   ########.fr       */
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
