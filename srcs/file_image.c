/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:34:34 by ebertin           #+#    #+#             */
/*   Updated: 2018/02/13 08:38:57 by ebertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*ft_convert(int nbr)
{
	char *str;

	str = (char*)malloc(sizeof(char) + 1);
	str[0] = nbr + 48;
	str[1] = '\0';
	return (str);
}

void	ammo(t_win_info *w)
{
	char *tmp;
	char *ammo;

	tmp = ft_convert(w->player.ammo);
	ammo = ft_strjoin(tmp, "/8");
	free(tmp);
	mlx_string_put(w->mlx, w->win, 10, 10, 0xEEEEEE, ammo);
	free(ammo);
}

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
