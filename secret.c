/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 23:21:17 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 23:24:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	change_secret(t_player *player, char **map)
{
	if (playerpcoll(1, *player, map) != 1)
		player->pos.x += ((player->wspeed - player->sspeed) * player->dir.x +
				(player->aspeed - player->dspeed) * player->dir.y) * 4.5;
	if (playerpcoll(0, *player, map) != 1)
		player->pos.y += ((player->wspeed - player->sspeed) * player->dir.y +
				(player->dspeed - player->aspeed) * player->dir.x) * 4.5;
}
