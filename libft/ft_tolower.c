/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 03:03:44 by smerelo           #+#    #+#             */
/*   Updated: 2017/11/27 22:17:56 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_tolower(int c)
{
	int a;

	a = c;
	if (c >= 'A' && c <= 'Z')
		a = (c + 32);
	return (a);
}