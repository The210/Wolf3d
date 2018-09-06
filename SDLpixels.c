/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLpixels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:30:14 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 20:32:06 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 *pixels = (Uint32 *)surface ->pixels;
	pixels[y * surface->w + x] = pixel;
}

Uint32	get_pixel32(SDL_Surface *surface, int x, int y)
{
	Uint32 pixel;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint32 color = 0;

	Uint32 *pixels = (Uint32*)surface->pixels;
	pixel = pixels[y*surface->w + x];
	SDL_LockSurface(surface);
	SDL_GetRGB( pixel, surface->format, &r, &g, &b );
	SDL_UnlockSurface(surface);
	color += r << 16;
	color += g << 8;
	color += b;
	return color;
}
