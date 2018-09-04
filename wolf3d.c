/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:50:47 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/04 19:15:11 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

char **readMap(char *argv)
{
	int fd;
	char *buf;
	int ret;
	char **map;
	char *str;
	str = ft_strnew(1);
	fd = open(argv, O_RDONLY);

	while (get_next_line(fd, &buf))
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if((map = ft_strsplit(str, ' ')) == NULL)
		return(NULL);
	if(str)
		ft_strdel(&str);
	return (map);
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel)
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

int collision(int i, int j, char **map)
{
	if (j >= ft_tablen(map) || ft_strlen(map[0]) <= i || i < 0 || j < 0)
		return (1);
	if (map[j][i] != '0' && map[j][i] != 'p' && map[j][i] != 's' && map[j][i] != 'S' && map[j][i] != 'C' && map[j][i] != 'O')
		return (1);
	if (map[j][i] == '0')
		return (0);
	else if (map[j][i] == 'p')
		return('p');
	else if (map[j][i] == 's')
		return ('s');
	else if (map[j][i] == 'C')
		return ('C');
	else if (map[j][i] == 'S')
		return(0);
	return (0);
}

t_cast *init_cast(t_cast *cast, t_player player)
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

void move_ray(t_cast *cast, t_player player, int *side)
{
	if (fabs(cast->dy/cast->dx) < fabs(cast->slope))
	{
		cast->x_pos = cast->x_pos + cast->dy/cast->slope;
		cast->y_pos = cast->y_pos + cast->dy;
		cast->j += cast->y_step;
		*side = 1;
		cast->Column = (int)(TEXTURE * (cast->x_pos - floor(cast->x_pos)));
	}
	else if (fabs(cast->dy/cast->dx) == fabs(cast->slope))
	{
		cast->x_pos += cast->dx;
		cast->y_pos += cast->dy;
		cast->i += cast->x_step;
		cast->j += cast->y_step;
		*side = (player.ray.y < player.ray.x);
		cast->Column = (int)(TEXTURE * (cast->x_pos - floor(cast->x_pos)));
	}
	else
	{
		cast->x_pos = cast->x_pos + cast->dx;
		cast->y_pos =  cast->y_pos + cast->slope * cast->dx;
		cast->i += cast->x_step;
		*side = 0;
		cast->Column = (int)(TEXTURE * (cast->y_pos - floor(cast->y_pos)));
	}
}

int vertical_ray(t_cast *cast, t_player player, int *side, char **map)
{
	cast->Column = (int)(TEXTURE * (cast->x_pos - floor(cast->x_pos)));
	*side = 1;
	cast->y_pos += floor(cast->y_pos) + (player.ray.y > 0) -
		(player.ray.y < 0) - cast->y_pos ;
	cast->j += cast->y_step;
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->y_pos += (player.ray.y > 0) - (player.ray.y < 0);
		cast->j += cast->y_step;
	}
	return SCREEN_HEIGHT / fabs(player.dir.x * (cast->x_pos - player.pos.x) +
			player.dir.y * (cast->y_pos - player.pos.y));
}

int	RayCast(t_player player, char **map, int* textureColumn, int *side, t_cast *cast)
{
	cast = init_cast(cast, player);
	if (!(fabs(player.ray.x) < cast->e))
		cast->slope = player.ray.y / player.ray.x;
	else 
		return (vertical_ray(cast, player, side, map));	
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->dx = player.ray.x > 0 ?  floor(cast->x_pos) + 1 - cast->x_pos :
			ceil(cast->x_pos) - 1 - cast->x_pos;
		cast->dy = player.ray.y > 0 ?  floor(cast->y_pos) + 1 - cast->y_pos :
			ceil(cast->y_pos) - 1 - cast->y_pos;
		move_ray(cast, player, side);
	}
	*textureColumn = cast->Column;
	return (SCREEN_HEIGHT / fabs(player.dir.x * (cast->x_pos - player.pos.x) +
				player.dir.y * (cast->y_pos - player.pos.y)));
}

int det_orient(int side, t_player player)
{
	if (side == 0)
		return (player.ray.x > 0 ? 1 : 2);
	else
		return (player.ray.y > 0 ? 3 : 4);
}

void draw_column(t_wind wind, t_misc misc)
{
	while (++misc.y < SCREEN_HEIGHT/2)
	{
		if (misc.y < misc.height)
		{ 
			misc.color = get_pixel32(wind.used, misc.textureColumn,
					TEXTURE/2 + floor(misc.y * misc.stepy) );
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH/2,
					SCREEN_HEIGHT/2 + misc.y, misc.color ) ;
			misc.color = get_pixel32(wind.used, misc.textureColumn,
					TEXTURE/2 - floor(misc.y * misc.stepy));
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH/2,
					SCREEN_HEIGHT/2 - misc.y, misc.color) ;
		}
		else
		{
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH/2,
					SCREEN_HEIGHT/2 - misc.y, 0x69B1B2);
			put_pixel32(wind.screen, misc.x - SCREEN_WIDTH/2,
					SCREEN_HEIGHT/2 + misc.y, 0x405135);
		}
	}
}

void RenderFrame(t_player player, t_wind wind, char **map, t_texture texture)
{
	t_misc misc;
	t_cast cast;

	misc.x = -(SCREEN_WIDTH / 2) - 1;
	misc.scale = 0.25 * (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	while (++misc.x < SCREEN_WIDTH/2)
	{	
		misc.y = -1;
		player.ray.x = player.dir.x + (player.plane.x * -misc.x / (SCREEN_WIDTH/2));
		player.ray.y = player.dir.y + (player.plane.y * -misc.x / (SCREEN_WIDTH/2));
		misc.height = misc.scale * RayCast(player, map, &misc.textureColumn, &misc.side, &cast) ;
		misc.stepy = (TEXTURE / 2) /(double) misc.height;
		misc.orientation = det_orient(misc.side, player);
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

int	playerCollision(int axis, t_player player, char **map )
{
	double nextXpos, nextYpos;
	double e = 0.3 ;


	if (axis)
	{
		nextXpos = player.pos.x + ( player.wSpeed - player.sSpeed ) * player.dir.x + ( player.aSpeed - player.dSpeed ) * player.dir.y;
		nextYpos = player.pos.y;
		return (collision((int)nextXpos, (int)nextYpos, map));
	}
	else
	{
		nextXpos = player.pos.x;
		nextYpos = player.pos.y + ( player.wSpeed - player.sSpeed ) * player.dir.y + ( player.dSpeed - player.aSpeed ) * player.dir.x;
		return (collision((int)nextXpos, (int)nextYpos, map));
	}

}

int	playerpcoll(int axis, t_player player, char **map )
{
	double nextXpos, nextYpos;
	double e = 0.3 ;


	if (axis)
	{
		nextXpos = player.pos.x + (( player.wSpeed - player.sSpeed ) * player.dir.x + ( player.aSpeed - player.dSpeed ) * player.dir.y) * 4.5;
		nextYpos = player.pos.y;
		return (collision((int)nextXpos, (int)nextYpos, map));
	}
	else
	{
		nextXpos = player.pos.x;
		nextYpos = player.pos.y + (( player.wSpeed - player.sSpeed ) * player.dir.y + ( player.dSpeed - player.aSpeed ) * player.dir.x) * 4.5;
		return (collision((int)nextXpos, (int)nextYpos, map));
	}

}
t_player init_player(t_player player, t_special special)
{
	player.dir.x = 1;
	player.dir.y = 0;
	player.angularSpeed = 0.09;
	player.speed = 0.2;
	player.runSpeed = 0.4;
	player.crouchSpeed = 0.1;
	player.pos.x = special.spawn.x + 0.501;
	player.pos.y = special.spawn.y + 0.501;
	return (player);
}

t_wind init_wind(t_wind wind)
{
	wind.screen = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError() ) ;
	else
		wind.window = SDL_CreateWindow( "Wolf3D by us", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) ;
	wind.screen = SDL_GetWindowSurface(wind.window) ;
	return (wind);
}

t_texture load_textures(t_texture texture)
{
	texture.north = SDL_LoadBMP("north.bmp");
	texture.south = SDL_LoadBMP("south.bmp");
	texture.east = SDL_LoadBMP("east.bmp");
	texture.west = SDL_LoadBMP("west.bmp");
	texture.portal = SDL_LoadBMP("portal.bmp");
	texture.door = SDL_LoadBMP("concrete.bmp");
	return (texture);
}

int check_key_down(t_player *player, t_wind wind, char **map)
{
	if(wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return 0;
	}
	//Looking
	if(wind.event.key.keysym.sym == SDLK_LEFT) //lookLeft
		player->thetaL = player->angularSpeed;
	if (wind.event.key.keysym.sym == SDLK_RIGHT) //lookright
		player->thetaR = player->angularSpeed;
	//Movement
	if (wind.event.key.keysym.sym == SDLK_w) //forward
		player->wSpeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_a) //left
		player->aSpeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_s) //backwards
		player->sSpeed = player->speed;
	if (wind.event.key.keysym.sym == SDLK_d) //right
		player->dSpeed = player->speed;
	//Modifiers
	if (wind.event.key.keysym.sym == KMOD_LSHIFT)
		printf("yeah\n");
	if (wind.event.key.keysym.sym == SDLK_e)
	{
		if (map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] == 'C' && map[(int)player->pos.y][(int)player->pos.x] != 'C')
			map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = 'O';
		else if (map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] == 'O' && map[(int)player->pos.y][(int)player->pos.x] != 'O')
			map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = 'C';
	}
	return (1);
}

void	change_char(t_player *player, t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_w)
		player->wSpeed = 0;
	if (wind.event.key.keysym.sym == SDLK_a)
		player->aSpeed = 0;
	if (wind.event.key.keysym.sym == SDLK_s)
		player->sSpeed = 0;
	if (wind.event.key.keysym.sym == SDLK_d)
		player->dSpeed = 0;
	if (wind.event.key.keysym.sym == SDLK_LEFT)
		player->thetaL = 0;
	if (wind.event.key.keysym.sym == SDLK_RIGHT)
		player->thetaR = 0;
}

void	change_comp(t_player *player, char **map, t_special special)
{
	double temp;
	temp = player->dir.x;
	player->dir.x = cos(player->thetaL - player->thetaR)*player->dir.x +
		sin(player->thetaL - player->thetaR)*player->dir.y;
	player->dir.y = cos(player->thetaL - player->thetaR)*player->dir.y -
		sin(player->thetaL - player->thetaR)*temp;
	if(playerCollision(1, *player, map ) != 1 && playerCollision(1, *player, map) != 'C')
		player->pos.x += (player->wSpeed - player->sSpeed) * player->dir.x +
			(player->aSpeed - player->dSpeed) * player->dir.y;
	if(playerCollision(0, *player, map) != 1 && playerCollision(0, *player, map) != 'C')
		player->pos.y += ( player->wSpeed - player->sSpeed ) * player->dir.y +
			(player->dSpeed - player->aSpeed) * player->dir.x;
	if (map[(int)player->pos.y][(int)player->pos.x] == 'p')
	{
		if ((int)player->pos.y == special.p1.y && (int)player->pos.x == special.p1.x)
		{
			player->pos.y += special.p2.y - special.p1.y;
			player->pos.x += special.p2.x - special.p1.x;
		}
		else
		{
			player->pos.y += special.p1.y - special.p2.y;
			player->pos.x += special.p1.x - special.p2.x;
		}
		if (playerpcoll(1, *player, map) != 1 && playerpcoll(1, *player, map) != 'C')
			player->pos.x += ((player->wSpeed - player->sSpeed) * player->dir.x +
					(player->aSpeed - player->dSpeed) * player->dir.y) * 4.5;
		if (playerpcoll(0, *player, map) != 1 && playerpcoll(0, *player, map) != 'C')
			player->pos.y += (( player->wSpeed - player->sSpeed ) * player->dir.y +
					(player->dSpeed - player->aSpeed) * player->dir.x) * 4.5;
	}
	if (map[(int)player->pos.y][(int)player->pos.x] == 's')
	{
		if (playerpcoll(1, *player, map) != 1)
			player->pos.x += ((player->wSpeed - player->sSpeed) * player->dir.x +
					(player->aSpeed - player->dSpeed) * player->dir.y) * 4.5;
		if (playerpcoll(0, *player, map) != 1)
			player->pos.y += (( player->wSpeed - player->sSpeed ) * player->dir.y +
					(player->dSpeed - player->aSpeed) * player->dir.x) * 4.5;
	}
	player->plane.x = player->dir.y;
	player->plane.y = -player->dir.x;
}

t_special	find_special(char **map, t_special special)
{
	int i;
	int j;
	int flag;
	int spawns;
	flag = 0;
	spawns = 0;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] && map[j][i] == 'p' && flag == 0)
			{
				special.p1.x = i;
				special.p1.y = j;
				flag = 1;
			}
			if (map[j][i] && map[j][i] == 'p' && flag == 1)
			{
				special.p2.x = i;
				special.p2.y = j;
			}
			if (map[j][i] && map[j][i] == 'S')
			{
				special.spawn.x = i;
				special.spawn.y = j;
				spawns++;
			}
		}
	}
	if (spawns == 1)
		special.error = 0;
	else
		special.error = 1;
	return (special);

}

int     main(int argc, char **argv)
{
	t_player player;
	t_wind wind;
	t_texture texture;
	t_special special;
	char **map;
	if (argc != 2)
		return (0);
	map = readMap(argv[1]);
	special = find_special(map, special);
	if (special.error == 1)
		return (1);
	player = init_player(player, special);
	wind = init_wind(wind);
	texture = load_textures(texture);
	while (1)
	{
		while(SDL_PollEvent(&wind.event))
		{
			if(wind.event.type == SDL_KEYDOWN)
			{
				if (check_key_down(&player, wind, map) == 0)
					return (0);
			}
			if (wind.event.type == SDL_KEYUP)
				change_char(&player, wind);
		}
		change_comp(&player, map, special);
		RenderFrame(player, wind, map, texture);
	}
	return (0) ;
}
