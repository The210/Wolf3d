/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:34:26 by smerelo           #+#    #+#             */
/*   Updated: 2018/08/15 04:07:14 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500



Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;
			break;

		case 2:
			return *(Uint16 *)p;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;

		case 4:
			return *(Uint32 *)p;
			break;

		default:
			return(0);
	}
}	
int		main(void)
{
	SDL_Window *window;
	SDL_Surface* image = NULL;
	SDL_Surface* image2 = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	else
		window = SDL_CreateWindow( "Wolf3D by us", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	image = SDL_GetWindowSurface(window);
	image2 = SDL_LoadBMP("gravel.bmp");
	SDL_LockSurface(image2);
	printf("%i\n", getpixel(image2, 2, 2));
	SDL_UnlockSurface(image2);
	SDL_BlitSurface(image2, NULL, image, NULL);	SDL_UpdateWindowSurface(window);
	sleep(30);
	return(0);
}
