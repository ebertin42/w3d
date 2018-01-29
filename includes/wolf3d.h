/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:40:35 by fde-souz          #+#    #+#             */
/*   Updated: 2018/01/29 22:03:30 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define SIZE_X 640
# define SIZE_Y 200
# define WALL	1;
# define SPAWN	3;
# define WALK	0;
# define BLOC	64;

typedef struct		s_intersection
{
	double			x;
	double			y;
}					t_intersection;

typedef struct		s_line
{
	int				nb_point;
	char			**line;
	int				cl;
}					t_line;

typedef struct		s_player
{
	double			start_x;
	double			start_y;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	int				fov;
}					t_player;

typedef struct		s_win_info
{
	void					*mlx;
	void					*win;
	t_player				player;
	double					map[32][32];
	int						s_wall;
	int						s_player;
}					t_win_info;

t_line				*read_data(char *file);
int					count_line_file(char *file);
int					check_good_nbdata(t_line *data);
int					translate(t_line *data, t_win_info *w);

#endif
