/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:50:52 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/06 21:13:03 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "SDL.h"
# include "libft.h"
# include "get_next_line.h"

# define SCREEN_HEIGHT 1000
# define SCREEN_WIDTH 1000
# define TEXTURE 500

typedef struct	s_pixels
{
	Uint32		*pixels;
	Uint32		pixel;
	Uint32		color;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_pixel;

typedef	struct	s_coord
{
	int			i;
	int			j;
}				t_coord;

typedef struct	s_cast
{
	double		x_pos;
	double		y_pos;
	int			object;
	int			i;
	int			j;
	int			x_step;
	int			y_step;
	double		dx;
	double		dy;
	double		slope;
	double		e;
	int			column;
}				t_cast;

typedef struct	s_misc
{
	int			x;
	int			y;
	int			height;
	int			texturecolumn;
	double		stepy;
	Uint32		color;
	int			side;
	int			orientation;
	double		scale;

}				t_misc;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_special
{
	t_vector	p1;
	t_vector	p2;
	t_vector	spawn;
	int			error;
}				t_special;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray;
	double		angularspeed;
	double		speed;
	double		runspeed;
	double		crouchspeed;
	double		thetal;
	double		thetar;
	double		wspeed;
	double		aspeed;
	double		sspeed;
	double		dspeed;
	int			error;
}				t_player;

typedef struct	s_wind
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*used;
	SDL_Event	event;
}				t_wind;

typedef struct	s_texture
{
	SDL_Surface	*north;
	SDL_Surface	*south;
	SDL_Surface	*west;
	SDL_Surface	*east;
	SDL_Surface	*portal;
	SDL_Surface	*door;
}				t_texture;

char			**readmap(char *argv);
t_player		init_player(t_player player, t_special special);
t_wind			init_wind(t_wind wind);
t_texture		load_textures(t_texture texture);
int				check_key_down(t_player *player, t_wind wind, char **map);
void			change_char(t_player *player, t_wind wind);
void			change_comp(t_player *player, char **map, t_special special);
int				playerpcoll(int axis, t_player player, char **map);
int				playercollision(int axis, t_player player, char **map);
int				collision(int i, int j, char **map);
int				playercollision(int axis, t_player player, char **map);
int				playerpcoll(int axis, t_player player, char **map);
void			put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			get_pixel32(SDL_Surface *surface, int x, int y);
t_cast			*init_cast(t_cast *cast, t_player player);
void			move_ray(t_cast *cast, t_player player, int *side);
int				vertical_ray(t_cast *cast, t_player player,
				int *side, char **map);
int				raycast(t_player player, char **map,
				t_misc *misc, t_cast *cast);
int				det_orient(int side, t_player player);
void			draw_column(t_wind wind, t_misc misc);
void			renderframe(t_player player, t_wind wind,
				char **map, t_texture texture);
void			change_secret(t_player *player, char **map);

#endif
