/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:53:47 by mploux            #+#    #+#             */
/*   Updated: 2018/04/22 18:15:02 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

float		clamp(float a, float min, float max)
{
	if (a < min)
		a = min;
	if (a > max)
		a = max;
	return (a);
}

int			balance(int min, int max, int v)
{
	int r;
	int diff;

	diff = (max - min);
	r = v % (max + diff);
	if (r > max)
		r = max - (r - diff);
	if (r < min)
		r = -r;
	return (r);
}

float		max_val(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float		min_val(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
