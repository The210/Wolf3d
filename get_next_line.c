/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:21:19 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/29 22:01:34 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	give_to_line(char **line, char *extra)
{
	char	*c;

	if ((c = ft_strchr(extra, '\n')))
	{
		*c = '\0';
		*line = ft_strdup(extra);
		c++;
		ft_memmove(extra, c, ft_strlen(c) + 1);
		return (1);
	}
	if (ft_strlen(extra) > 0)
	{
		*line = ft_strdup(extra);
		*extra = '\0';
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*extra = NULL;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	if (!line || fd < 0)
		return (-1);
	if (extra == NULL)
		extra = ft_strnew(0);
	while (!ft_strchr(extra, '\n'))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (give_to_line(line, extra));
		buf[ret] = '\0';
		if (buf[0] && buf[0] != 'p' && buf[0] != '\n' && buf[0] != 'C' &&
		buf[0] != '0' && buf[0] != '1' && buf[0] != 'S' && buf[0] != 's')
			return (-1);
		tmp = ft_strjoin(extra, buf);
		ft_strdel(&extra);
		extra = tmp;
	}
	return (give_to_line(line, extra));
}
