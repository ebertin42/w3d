/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:40:35 by fde-souz          #+#    #+#             */
/*   Updated: 2018/02/13 19:37:46 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <signal.h>

# define SIZE_X 720
# define SIZE_Y 480
# define BLOC	128.00
# define IBLOC	128
# define RAD	(M_PI / 180.00)
# define WIN_X 720
# define WIN_Y 480
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
# define DEL	51
# define SPACE	49

typedef struct		s_menu
{
	int				statut;
	int				link;
	int				set;
	int				change;
	int				token_set;
	int				gameover_menu;
	int				go;
	void			*menu;
	void			*settings;
	void			*credits;
	void			*bombe;
	void			*gameover;
}					t_menu;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_intersection
{
	double			x;
	double			y;
	int				dist;
	int				token;
	int				obstacle;
}					t_intersection;

typedef struct		s_obstacle
{
	int				h;
	int				dist;
	int				texid;
	int				col;
	int				token;
}					t_obstacle;

typedef struct		s_all_ob
{
	t_obstacle		ob;
	t_obstacle		ob_mob;
	t_obstacle		ob_mob_dead;
}					t_all_ob;

typedef struct		s_raycasting
{
	t_intersection	a;
	t_intersection	b;
	t_intersection	a_mob;
	t_intersection	b_mob;
}					t_raycasting;

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
	int				ammo;
	int				score;
	int				forward;
	int				backward;
	int				left;
	int				right;
}					t_player;

typedef struct		s_img
{
	void			*img;
	char			*str;
	int				b;
	int				s;
	int				e;
}					t_img;

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_hit_mob
{
	int				token;
	t_intersection	a;
	t_intersection	b;
}					t_hit_mob;

typedef struct		s_win_info
{
	char			*str;
	void			*mlx;
	void			*win;
	void			*menu;
	t_player		player;
	t_img			img;
	t_img			tex[9];
	t_img			sky;
	double			map[32][32];
	double			dist_player_proj;
	int				s_player;
	int				id;
	pid_t			pid;
	t_menu			m;
}					t_win_info;

t_line				*read_data(char *file);
int					count_line_file(char *file);
int					check_good_nbdata(t_line *data);
int					translate(t_line *data, t_win_info *w);
int					raycasting(t_win_info w, int test);
void				put_pixel_image(int x, int y, int color, t_win_info *w);
double				conv_rad(double angle);
void				cursor(t_win_info *w);
void				map_error(int error);
void				read_error(int error);
void				hud(t_win_info *w);
void				image_hud(t_win_info *w);
int					get_color(int y, t_win_info w, t_obstacle ob);
void				draw(int x, t_win_info *w, t_obstacle ob);
int					load_texture_mur(t_win_info *w);
int					load_texture_sprite(t_win_info *w);
void				put_sprite_wep(t_win_info *w, int texid);
void				child();
void				file_image(t_win_info *w);
void				ammo(t_win_info *w);
void				ennemies_place(double tab[32][32]);
int					mob_detection(t_obstacle *ob, t_win_info w, double alpha,
		int state);
int					wall_detection(t_obstacle *ob, t_win_info w, double alpha);
t_intersection		find_intersection_ver(double alpha, t_win_info w, \
		int obstacle);
t_intersection		find_intersection_hor(double alpha, t_win_info w, \
		int obstacle);
int					key_hook(int key, void *param);
int					ft_close(int keycode, void *param);
int					menu(int keycode, t_win_info *w);
void				init_data(t_win_info *w, int token);
void				backward(t_win_info *w, double angle, int speed);
void				forward(t_win_info *w, double angle, int speed);
void				game_over(t_win_info *w, int key);
void				menu_bombe(t_win_info w, int x, int y, int token);
void				new_game(t_win_info *w);
void				message_change(t_win_info *w);
int					key_release(int key, void *param);

#endif
