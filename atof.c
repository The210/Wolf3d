/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 02:42:17 by smerelo           #+#    #+#             */
/*   Updated: 2018/08/17 05:05:03 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

float		atof(char *nbr)
{
	float r;
	int i;
	int f;
	int f3;
	f3 = 0;
	f = 0;
	r = 0;
	i = -1;
	while(nbr[++i])
	{
		if (nbr[i] == '-')
		{
			f = 1;
			i++;
		}
		if (nbr[i] == '.')
		{
			f3 = i;
			i++;
		}
		if (f3 == 0)
			r = (r * 10) + nbr[i] - '0';
		else
		{
			r = r + (nbr[i] - '0') / pow(10.0, i - f3);
		}
	}
	if (f == 1)
		r *= -1;
	return(r);
}

int		main(int ac, char **av)
{
	printf("%f\n", atof(av[1]));
	return(0);
}
