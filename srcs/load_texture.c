/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:45:56 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/13 16:09:54 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	load_texture_mur(t_win_info *w)
{
	int a;
	int b;

	w->tex[0].img = mlx_xpm_file_to_image(w->mlx, "./assets/brick.XPM", &a, &b);
	w->tex[1].img = mlx_xpm_file_to_image(w->mlx, "./assets/bois.XPM", &a, &b);
	w->tex[2].img = mlx_xpm_file_to_image(w->mlx, "./assets/brikb.XPM", &a, &b);
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

int	load_texture_sprite(t_win_info *w)
{
	int a;
	int b;

	w->tex[4].img = mlx_xpm_file_to_image(w->mlx,
		"./assets/MP-Frame2.XPM", &a, &b);
	w->tex[5].img = mlx_xpm_file_to_image(w->mlx,
		"./assets/MP-Frame3.XPM", &a, &b);
	w->tex[6].img = mlx_xpm_file_to_image(w->mlx,
		"./assets/MP-Frame4.XPM", &a, &b);
	w->tex[7].img = mlx_xpm_file_to_image(w->mlx, "./assets/hitle.XPM", &a, &b);
	w->tex[8].img = mlx_xpm_file_to_image(w->mlx, "./assets/dead.XPM", &a, &b);
	if (!(w->tex[4].img || w->tex[5].img || w->tex[6].img || w->tex[7].img))
		return (0);
	w->tex[4].str = mlx_get_data_addr(w->tex[4].img,
									&w->tex[4].b, &w->tex[4].s, &w->tex[4].e);
	w->tex[5].str = mlx_get_data_addr(w->tex[5].img,
									&w->tex[5].b, &w->tex[5].s, &w->tex[5].e);
	w->tex[6].str = mlx_get_data_addr(w->tex[6].img,
									&w->tex[6].b, &w->tex[6].s, &w->tex[6].e);
	w->tex[7].str = mlx_get_data_addr(w->tex[7].img,
									&w->tex[7].b, &w->tex[7].s, &w->tex[7].e);
	w->tex[8].str = mlx_get_data_addr(w->tex[8].img,
									&w->tex[8].b, &w->tex[8].s, &w->tex[8].e);
	return (1);
}
