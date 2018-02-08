/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:45:56 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/08 15:36:36 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	load_texture(t_win_info *w)
{
	int a;
	int b;

	w->tex[0].img = mlx_xpm_file_to_image(w->mlx, "./assets/brick.XPM", &a, &b);
	w->tex[1].img = mlx_xpm_file_to_image(w->mlx, "./assets/bois.XPM", &a, &b);
	w->tex[2].img = mlx_xpm_file_to_image(w->mlx, "./assets/brickbleus.XPM", &a, &b);
	w->tex[3].img = mlx_xpm_file_to_image(w->mlx, "./assets/metal.XPM", &a, &b);
	if (!(w->tex[0].img || w->tex[1].img || w->tex[2].img || w->tex[3].img))
		return (0);
	w->tex[0].str = mlx_get_data_addr(w->tex[0].img,
									&w->tex[0].b, &w->tex[0].s, &w->tex[0].e);
	w->tex[1].str = mlx_get_data_addr(w->tex[1].img,
									&w->tex[1].b, &w->tex[1].s, &w->tex[1].e);
	w->tex[2].str = mlx_get_data_addr(w->tex[2].img,
									&w->tex[2].b, &w->tex[2].s, &w->tex[2].e);
	w->tex[3].str = mlx_get_data_addr(w->tex[3].img,
									&w->tex[3].b, &w->tex[3].s, &w->tex[3].e);
	return (1);
}
