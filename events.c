/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:12:57 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 23:25:59 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	open_door(t_player *player, char **map)
{
	if (map[(int)(player->pos.y + player->dir.y)]
	[(int)(player->pos.x + player->dir.x)] == 'C'
	&& map[(int)player->pos.y][(int)player->pos.x] != 'C')
		map[(int)(player->pos.y + player->dir.y)]
		[(int)(player->pos.x + player->dir.x)] = 'O';
	else if (map[(int)(player->pos.y + player->dir.y)]
			[(int)(player->pos.x + player->dir.x)] == 'O'
			&& map[(int)player->pos.y][(int)player->pos.x] != 'O')
		map[(int)(player->pos.y + player->dir.y)]
		[(int)(player->pos.x + player->dir.x)] = 'C';
}

int		check_key_down(t_player *player, t_wind wind, char **map)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (0);
	}
	if (wind.event.key.keysym.sym == SDLK_LEFT)
		player->thetal = player->angularspeed;
	if (wind.event.key.keysym.sym == SDLK_RIGHT)
		player->thetar = player->angularspeed;
	if (wind.event.key.keysym.sym == SDLK_w)
		player->wspeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_a)
		player->aspeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_s)
		player->sspeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_d)
		player->dspeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_e)
		open_door(player, map);
	return (1);
}

void	change_char(t_player *player, t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_w)
		player->wspeed = 0;
	if (wind.event.key.keysym.sym == SDLK_a)
		player->aspeed = 0;
	if (wind.event.key.keysym.sym == SDLK_s)
		player->sspeed = 0;
	if (wind.event.key.keysym.sym == SDLK_d)
		player->dspeed = 0;
	if (wind.event.key.keysym.sym == SDLK_LEFT)
		player->thetal = 0;
	if (wind.event.key.keysym.sym == SDLK_RIGHT)
		player->thetar = 0;
}

void	portal_change(t_player *player, t_special special, char **map)
{
	if ((int)player->pos.y == special.p1.y &&
	(int)player->pos.x == special.p1.x)
	{
		player->pos.y += special.p2.y - special.p1.y;
		player->pos.x += special.p2.x - special.p1.x;
	}
	else
	{
		player->pos.y += special.p1.y - special.p2.y;
		player->pos.x += special.p1.x - special.p2.x;
	}
	if (playerpcoll(1, *player, map) != 1 &&
	playerpcoll(1, *player, map) != 'C')
		player->pos.x += ((player->wspeed - player->sspeed) * player->dir.x +
				(player->aspeed - player->dspeed) * player->dir.y) * 4.5;
	if (playerpcoll(0, *player, map) != 1 &&
	playerpcoll(0, *player, map) != 'C')
		player->pos.y += ((player->wspeed - player->sspeed) * player->dir.y +
				(player->dspeed - player->aspeed) * player->dir.x) * 4.5;
}

void	change_comp(t_player *player, char **map, t_special special)
{
	double temp;

	temp = player->dir.x;
	player->dir.x = cos(player->thetal - player->thetar) * player->dir.x +
		sin(player->thetal - player->thetar) * player->dir.y;
	player->dir.y = cos(player->thetal - player->thetar) * player->dir.y -
		sin(player->thetal - player->thetar) * temp;
	if (playercollision(1, *player, map) != 1
	&& playercollision(1, *player, map) != 'C')
		player->pos.x += (player->wspeed - player->sspeed) * player->dir.x +
			(player->aspeed - player->dspeed) * player->dir.y;
	if (playercollision(0, *player, map) != 1
	&& playercollision(0, *player, map) != 'C')
		player->pos.y += (player->wspeed - player->sspeed) * player->dir.y +
			(player->dspeed - player->aspeed) * player->dir.x;
	if (map[(int)player->pos.y][(int)player->pos.x] == 'p')
		portal_change(player, special, map);
	if (map[(int)player->pos.y][(int)player->pos.x] == 's')
		change_secret(player, map);
	player->plane.x = player->dir.y;
	player->plane.y = -player->dir.x;
}
