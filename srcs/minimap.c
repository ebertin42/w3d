/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 16:00:27 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/16 11:14:01 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_map(t_win_info *w, int x, int y, int m_color)
{
	x += 10;
	y += 10;
	put_pixel_image(x, y, m_color, w);
	put_pixel_image(x + 1, y, m_color, w);
	put_pixel_image(x + 2, y, m_color, w);
	put_pixel_image(x, y + 1, m_color, w);
	put_pixel_image(x + 1, y + 1, m_color, w);
	put_pixel_image(x + 2, y + 1, m_color, w);
	put_pixel_image(x, y + 2, m_color, w);
	put_pixel_image(x + 1, y + 2, m_color, w);
	put_pixel_image(x + 2, y + 2, m_color, w);
}

void	minimap(t_win_info *w)
{
	t_minimap m;

	m.i = 0;
	m.x = 0;
	while (m.x < 32)
	{
		m.y = 0;
		m.j = 0;
		while (m.y < 32)
		{
			if (w->map[m.x][m.y] == WALL)
				print_map(w, m.x + m.i, m.y + m.j, 0xFFFFFF);
			else if (w->map[m.x][m.y] == MONSTER)
				print_map(w, m.x + m.i, m.y + m.j, 0xFF0000);
			else
				print_map(w, m.x + m.i, m.y + m.j, 0x0000FF);
			if ((int)(w->player.pos_x / 128) == m.y &&
					(int)(w->player.pos_y / 128) == m.x)
				print_map(w, m.x + m.i, m.y + m.j, 0x05F000);
			m.y++;
			m.j += 3;
		}
		m.x++;
		m.i += 3;
	}
}
