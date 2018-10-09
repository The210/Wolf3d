/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:02:37 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/30 20:49:32 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			check_map(char **map)
{
	int		i;
	int		j;
	size_t	c;
	int		r;
	int		p;

	if (!map[0])
		return (0);
	p = 0;
	c = ft_strlen(map[0]);
	i = -1;
	while (map[++i])
	{
		r = ft_strlen(map[i]) != c ? 0 : 1;
		j = -1;
		while (map[i][++j])
		{
			if ((map[0][j] != '1') || (map[i][0] != '1') || (map[i]
	[ft_strlen(map[0]) - 1] != '1') || (map[ft_tablen(map) - 1][j] != '1'))
				return (0);
		}
	}
	return (r);
}

char		**readmap(char *argv)
{
	int		fd;
	char	*buf;
	int		ret;
	char	**map;
	char	*str;

	str = ft_strnew(1);
	fd = open(argv, O_RDONLY);
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if ((map = ft_strsplit(str, ' ')) == NULL
		|| ret == -1 || check_map(map) == 0)
	{
		ft_putendl("Error: invalid file");
		return (NULL);
	}
	if (str)
		ft_strdel(&str);
	return (map);
}

void		init_player(t_special special, t_player *player)
{
	player->error = 0;
	player->dir.x = 1;
	player->dir.y = 0;
	player->angularspeed = 0.07;
	player->speed = 0.1;
	player->pos.x = special.spawn.x + 0.501;
	player->pos.y = special.spawn.y + 0.501;
}

void		init_wind(t_wind *wind)
{
	wind->screen = NULL;
	wind->window = SDL_CreateWindow("Wolf3D by us", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	wind->screen = SDL_GetWindowSurface(wind->window);
}

void		load_textures(t_texture *texture)
{
	texture->north = SDL_LoadBMP("textures/north.bmp");
	texture->south = SDL_LoadBMP("textures/south.bmp");
	texture->east = SDL_LoadBMP("textures/east.bmp");
	texture->west = SDL_LoadBMP("textures/west.bmp");
	texture->portal = SDL_LoadBMP("textures/portal.bmp");
	texture->door = SDL_LoadBMP("textures/concrete.bmp");
}
