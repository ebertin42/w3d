/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 19:31:28 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/12 16:24:33 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	map_error(int error)
{
	if (error == 0)
	{
		ft_putstr("\nSPAWN ERROR :");
		ft_putstr("\n - the spawn have to be surrounded by walkable area.");
		ft_putstr("\n - the spawn have to be unique in the map.");
		ft_putstr("\n - the number associated to the span is '3'.\n\n");
	}
	else if (error == 1)
		ft_putstr("\nMAP ERROR:\n - the map is not a 32x32 map\n\n");
	else if (error == 2)
		ft_putstr("\nMAP ERROR:\n - the border are not full of wall\n\n");
	else if (error == 4)
		ft_putstr("\nMAP ERROR:\n - ennemies are not on the good place\n\n");
	exit(0);
}

void	read_error(int error)
{
	if (error == 0)
		ft_putstr("\nOPEN ERROR:\n - the file is not valid file.\n\n");
	else if (error == 1)
		ft_putstr("\nREAD ERROR:\n - the file can't be read.\n\n");
	exit(0);
}
