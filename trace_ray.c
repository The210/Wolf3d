/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:37:51 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/06 20:39:00 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_cast	*init_cast(t_cast *cast, t_player player)
{
	cast->x_pos = player.pos.x;
	cast->y_pos = player.pos.y;
	cast->i = (int)player.pos.x;
	cast->j = (int)player.pos.y;
	cast->e = 0.00000001;
	cast->x_step = player.ray.x > 0 ? 1 : -1;
	cast->y_step = player.ray.y > 0 ? 1 : -1;
	return (cast);
}

void	move_ray(t_cast *cast, t_player player, int *side)
{
	if (fabs(cast->dy / cast->dx) < fabs(cast->slope))
	{
		cast->x_pos = cast->x_pos + cast->dy / cast->slope;
		cast->y_pos = cast->y_pos + cast->dy;
		cast->j += cast->y_step;
		*side = 1;
		cast->column = (int)(TEXTURE * (cast->x_pos - floor(cast->x_pos)));
	}
	else if (fabs(cast->dy / cast->dx) == fabs(cast->slope))
	{
		cast->x_pos += cast->dx;
		cast->y_pos += cast->dy;
		cast->i += cast->x_step;
		cast->j += cast->y_step;
		*side = (player.ray.y < player.ray.x);
		cast->column = (int)(TEXTURE * (cast->x_pos - floor(cast->x_pos)));
	}
	else
	{
		cast->x_pos = cast->x_pos + cast->dx;
		cast->y_pos = cast->y_pos + cast->slope * cast->dx;
		cast->i += cast->x_step;
		*side = 0;
		cast->column = (int)(TEXTURE * (cast->y_pos - floor(cast->y_pos)));
	}
}

int		vertical_ray(t_cast *cast, t_player player, int *side, char **map)
{
	cast->column = (int)(TEXTURE * (cast->x_pos - floor(cast->x_pos)));
	*side = 1;
	cast->y_pos += floor(cast->y_pos) + (player.ray.y > 0) -
		(player.ray.y < 0) - cast->y_pos;
	cast->j += cast->y_step;
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->y_pos += (player.ray.y > 0) - (player.ray.y < 0);
		cast->j += cast->y_step;
	}
	return (SCREEN_HEIGHT / fabs(player.dir.x * (cast->x_pos - player.pos.x) +
			player.dir.y * (cast->y_pos - player.pos.y)));
}

int		raycast(t_player player, char **map, t_misc *misc, t_cast *cast)
{
	cast = init_cast(cast, player);
	if (!(fabs(player.ray.x) < cast->e))
		cast->slope = player.ray.y / player.ray.x;
	else
		return (vertical_ray(cast, player, &misc->side, map));
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->dx = player.ray.x > 0 ? floor(cast->x_pos) + 1 - cast->x_pos :
		ceil(cast->x_pos) - 1 - cast->x_pos;
		cast->dy = player.ray.y > 0 ? floor(cast->y_pos) + 1 - cast->y_pos :
		ceil(cast->y_pos) - 1 - cast->y_pos;
		move_ray(cast, player, &misc->side);
	}
	misc->texturecolumn = cast->column;
	return (SCREEN_HEIGHT / fabs(player.dir.x * (cast->x_pos - player.pos.x) +
				player.dir.y * (cast->y_pos - player.pos.y)));
}
