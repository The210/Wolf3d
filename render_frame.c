/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 21:37:53 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 23:45:35 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		det_orient(int side, t_player player)
{
	if (side == 0)
		return (player.ray.x > 0 ? 1 : 2);
	else
		return (player.ray.y > 0 ? 3 : 4);
}

void	draw_column(t_wind wind, t_misc misc)
{
	while (++misc.y < SCREEN_HEIGHT / 2)
	{
		if (misc.y < misc.height)
		{
			misc.color = get_pixel32(wind.used, misc.texturecolumn,
					TEXTURE / 2 + floor(misc.y * misc.stepy));
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2 + misc.y, misc.color);
			misc.color = get_pixel32(wind.used, misc.texturecolumn,
					TEXTURE / 2 - floor(misc.y * misc.stepy));
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2 - misc.y, misc.color);
		}
		else
		{
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2 - misc.y, 0x69B1B2);
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2 + misc.y, 0x405135);
		}
	}
}

void	rays(t_player *player, t_misc *misc, t_cast *cast, char **map)
{
	misc->y = -1;
	player->ray.x = player->dir.x + (player->plane.x * -misc->x
			/ (SCREEN_WIDTH / 2));
	player->ray.y = player->dir.y + (player->plane.y * -misc->x
			/ (SCREEN_WIDTH / 2));
	misc->height = misc->scale * RayCast(*player, map,
			&misc->texturecolumn, &misc->side, cast);
	misc->stepy = (TEXTURE / 2) / (double)misc->height;
	misc->orientation = det_orient(misc->side, *player);
}

void	renderframe(t_player player, t_wind wind, char **map, t_texture texture)
{
	t_misc misc;
	t_cast cast;

	misc.x = -(SCREEN_WIDTH / 2) - 1;
	misc.scale = 0.25 * (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	while (++misc.x < SCREEN_WIDTH / 2)
	{
		rays(&player, &misc, &cast, map);
		if (cast.object == 'p')
			wind.used = texture.portal;
		else if (cast.object == 'C')
			wind.used = texture.door;
		else if (misc.side == 1)
			wind.used = misc.orientation == 3 ? texture.north : texture.south;
		else
			wind.used = misc.orientation == 1 ? texture.east : texture.west;
		draw_column(wind, misc);
	}
	SDL_UpdateWindowSurface(wind.window);
}
