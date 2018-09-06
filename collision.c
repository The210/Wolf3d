/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:24:05 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 23:33:23 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	collision(int i, int j, char **map)
{
	if (j >= ft_tablen(map) || ft_strlen(map[0]) <= i || i < 0 || j < 0)
		return (1);
	if (map[j][i] != '0' && map[j][i] != 'p' && map[j][i] != 's' &&
	map[j][i] != 'S' && map[j][i] != 'C' && map[j][i] != 'O')
		return (1);
	if (map[j][i] == '0')
		return (0);
	else if (map[j][i] == 'p')
		return ('p');
	else if (map[j][i] == 's')
		return ('s');
	else if (map[j][i] == 'C')
		return ('C');
	else if (map[j][i] == 'S')
		return (0);
	return (0);
}

int	playercollision(int axis, t_player player, char **map)
{
	double	nextxpos;
	double	nextypos;
	double	e;

	e = 0.3;
	if (axis)
	{
		nextxpos = player.pos.x + (player.wspeed - player.sspeed) * player.dir.x
		+ (player.aspeed - player.dspeed) * player.dir.y;
		nextypos = player.pos.y;
		return (collision((int)nextxpos, (int)nextypos, map));
	}
	else
	{
		nextxpos = player.pos.x;
		nextypos = player.pos.y + (player.wspeed - player.sspeed) * player.dir.y
		+ (player.dspeed - player.aspeed) * player.dir.x;
		return (collision((int)nextxpos, (int)nextypos, map));
	}
}

int	playerpcoll(int axis, t_player player, char **map)
{
	double	nextxpos;
	double	nextypos;
	double	e;

	e = 0.3;
	if (axis)
	{
		nextxpos = player.pos.x + ((player.wspeed - player.sspeed) *
				player.dir.x
		+ (player.aspeed - player.dspeed) * player.dir.y) * 4.5;
		nextypos = player.pos.y;
		return (collision((int)nextxpos, (int)nextypos, map));
	}
	else
	{
		nextxpos = player.pos.x;
		nextypos = player.pos.y + ((player.wspeed - player.sspeed) *
				player.dir.y
		+ (player.dspeed - player.aspeed) * player.dir.x) * 4.5;
		return (collision((int)nextxpos, (int)nextypos, map));
	}
}
