/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectorlib.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: root <root@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 21:57:49 by root          #+#    #+#                 */
/*   Updated: 2022/12/16 22:00:38 by root          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double		dot(t_vec a, t_vec b)
{
	double ret;

	ret =  (a[X] * b[X]) + (a[Y] * b[Y]) + (a[Z] * b[Z]);
	return (ret);
}

t_vec		cross(t_vec a, t_vec b)
{
	t_vec	cross;

	cross[X] = (a[Y] * b[Z]) - (a[Z] * b[Y]);
	cross[Y] = (a[Z] * b[X]) - (a[X] * b[Z]);
	cross[Z] = (a[X] * b[Y]) - (a[Y] * b[X]);
	return (cross);
}

double		sqr(double x)
{
	return (x * x);
}

double		vec_length_squared(t_vec vec)
{
	return (sqr(vec[X]) + sqr(vec[Y]) + sqr(vec[Z]));
}

double		vec_length(t_vec vec)
{
	return (sqrt(vec_length_squared(vec)));
}