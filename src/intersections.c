/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersections.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 03:30:22 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/20 07:57:12 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//maybe turn sphere into *sphere?
bool	hit_sphere(t_obj sphere, const t_ray *ray, t_inter *intersection)
{
	t_vec	aligned;
	double	discriminant;
	double	a;
	double	b;
	double	c;
	
	aligned = ray->origin - sphere.pos;
	a = dot(ray->direction, ray->direction);
	// b = 2.0 * dot(aligned, ray->direction);
	b = dot(aligned, ray->direction);
	c = dot(aligned, aligned) - sqr(sphere.diameter / 2);
	discriminant = b * b - a * c;
	// discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0.0f)
		return (false);

	// printf ("max = %f\n", intersection->t);
	double	min;
	double	plus;
	min = (-b - sqrt(b * b - a * c) / a);
	plus = (-b + sqrt(b * b - a * c) / a);
	//todo: get rid of tmp <= instead use tmp < ?
	if (min > RAY_T_MIN && min < intersection->t)
		intersection->t = min;
	else if (plus > RAY_T_MIN && plus < intersection->t)
		intersection->t = plus;
	else
		return (false);
	intersection->obj = &sphere;
	intersection->colour = sphere.colour;
	return (true);
}

