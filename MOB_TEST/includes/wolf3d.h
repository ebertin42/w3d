/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:40:35 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/08 13:55:43 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define SIZE_X 640.00
# define SIZE_Y 400.00
# define BLOC	256.00
# define RAD	(M_PI / 180.00)
# define WIN_X 720
# define WIN_Y 480
# define SIZE_X 640.00
# define SIZE_Y 400.00
# define WALL	1
# define SPAWN	3
# define WALK	0
# define MONSTER 7
# define FORWARD	13
# define BACKWARD	1
# define LEFT		0
# define RIGHT		2
# define KEY_ESC	53
# define SPRINT		257

typedef struct		s_intersection
{
	double			x;
	double			y;
}					t_intersection;

typedef struct		s_rectangle
{
	int				x;
	int				y;
	int				color;
	int				hei;
	int				len;
}					t_rectangle;

typedef struct		s_line
{
	int				nb_point;
	int				cl;
	char			**line;
}					t_line;

typedef struct		s_player
{
	double			start_x;
	double			start_y;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			fov;
	int				sprint;
	int				life;
}					t_player;

typedef struct		s_img
{
	void			*img;
	char			*str;
	int				b;
	int				s;
	int				e;
}					t_img;

typedef struct		s_win_info
{
	void			*mlx;
	void			*win;
	t_player		player;
	t_img			img;
	t_img			tex;
	double			map[32][32];
	double			dist_player_proj;
	int				s_player;
}					t_win_info;

t_line				*read_data(char *file);
int					count_line_file(char *file);
int					check_good_nbdata(t_line *data);
int					translate(t_line *data, t_win_info *w);
int					raycasting(t_win_info w);
void				put_pixel_image(int x, int y, int color, t_win_info *w);
double				conv_rad(double angle);
void				cursor(t_win_info *w);
void				map_error(int error);
void				read_error(int error);
void				hud(t_win_info *w);
void				image_hud(t_win_info *w);
int					get_color(int y, int h_wall, int column, t_win_info w);
void				draw(int x, int h_wall, t_win_info *w, int column);
#endif