/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:50:47 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/30 20:51:36 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		find_s2(char **map, t_special *special, t_coord *s, t_coord *fs)
{
	s->i = -1;
	while (map[s->j][++s->i])
	{
		if (map[s->j][s->i] && map[s->j][s->i] == 'p' && fs->i > 0)
		{
			special->p2.x = s->i;
			special->p2.y = s->j;
			fs->i++;
		}
		if (map[s->j][s->i] && map[s->j][s->i] == 'p' && fs->i == 0)
		{
			special->p1.x = s->i;
			special->p1.y = s->j;
			fs->i++;
		}
		if (map[s->j][s->i] && map[s->j][s->i] == 'S')
		{
			special->spawn.x = s->i;
			special->spawn.y = s->j;
			fs->j++;
		}
	}
}

void		find_special(char **map, t_special *special)
{
	t_coord		s;
	t_coord		fs;

	fs.i = 0;
	fs.j = 0;
	s.j = -1;
	while (map[++s.j])
		find_s2(map, special, &s, &fs);
	if ((fs.i == 2 || fs.i == 0) && fs.j == 1)
		special->error = 0;
	else
	{
		ft_putendl("Error: Incorrect map.");
		special->error = 1;
	}
}

t_player	loop(t_wind wind, t_player player, char **map, t_special special)
{
	while (SDL_PollEvent(&wind.event))
	{
		if (wind.event.type == SDL_QUIT)
		{
			SDL_DestroyWindow(wind.window);
			SDL_Quit();
			player.error = 1;
		}
		if (wind.event.type == SDL_KEYDOWN)
		{
			if (check_key_down(&player, wind, map) == 0)
				player.error = 1;
		}
		if (wind.event.type == SDL_KEYUP)
			change_char(&player, wind);
	}
	change_comp(&player, map, special);
	return (player);
}

int			main(int argc, char **argv)
{
	t_player	player;
	t_wind		wind;
	t_texture	texture;
	t_special	special;
	char		**map;

	if (argc != 2)
		return (0);
	if ((map = readmap(argv[1])) == NULL)
		return (1);
	find_special(map, &special);
	if (special.error == 1)
		return (1);
	init_player(special, &player);
	init_wind(&wind);
	load_textures(&texture);
	while (1)
	{
		player = loop(wind, player, map, special);
		if (player.error == 1)
			return (0);
		renderframe(player, wind, map, texture);
	}
	return (0);
}
