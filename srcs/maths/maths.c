/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:53:47 by mploux            #+#    #+#             */
/*   Updated: 2018/04/23 20:47:09 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

float		clamp(float a, float min, float max)
{
	float r;

	r = a;
	if (r < min)
		r = min;
	if (r > max)
		r = max;
	return (r);
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
