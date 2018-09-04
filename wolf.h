/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:50:52 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 17:53:08 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include <unistd.h>
#include "SDL.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 1000
#define TEXTURE 500

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
	int			Column;
}				t_cast;



typedef struct	s_misc
{
	int			x;
	int			y;
	int			height;
	int			textureColumn;
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

typedef struct  s_special
{
	t_vector	p1;
	t_vector	p2;
	t_vector	spawn;
	int			error;
}				t_special;

typedef struct	s_player
{
	t_vector pos;
	t_vector dir;
	t_vector plane;
	t_vector ray;
	double angularSpeed;
	double speed;
	double runSpeed;
	double crouchSpeed;
	double thetaL;
	double thetaR;
	double wSpeed;
	double aSpeed;
	double sSpeed;
	double dSpeed;
}		t_player;

typedef struct	s_wind
{
	SDL_Window *window;
	SDL_Surface *screen;
	SDL_Surface *used;
        SDL_Event event;	
}		t_wind;

typedef struct	s_texture
{
	SDL_Surface *north;
	SDL_Surface *south;
	SDL_Surface *west;
	SDL_Surface *east;
	SDL_Surface *portal;
}		t_texture;

#endif
