/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersections.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 03:30:22 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 23:43:51 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//maybe turn sphere into *sphere?
bool	hit_sphere(t_obj *sphere, t_ray *ray, t_inter *intersection)
{
	t_vec	aligned;
	double	discriminant;
	double	a;
	double	b;
	double	c;
	
	aligned = ray->origin - sphere->pos;
	// a = dot(ray->direction, ray->direction);
	a = vec_length_squared(ray->direction);
	b = dot(aligned, ray->direction);
	c = dot(aligned, aligned) - sqr(sphere->diameter / 2);
	discriminant = b * b - a * c;
	if (discriminant < 0.0f)
		return (false);

	// printf ("max = %f\n", intersection->t);
	double	min;
	double	plus;
	min = (-b - sqrt(discriminant)) / a;
	plus = (-b + sqrt(discriminant)) / a;
	if (min > RAY_T_MIN && min < intersection->t)
	{
		intersection->t = min;
	}
	else if (plus > RAY_T_MIN && plus < intersection->t)
	{
		intersection->t = plus;
	}
	else
		return (false);
	intersection->ray = *ray;
	intersection->obj = sphere;
	intersection->colour = sphere->colour;
	intersection->p = ray_at_t(ray, intersection->t);
	intersection->material = sphere->material;
	intersection->fuzzy = sphere->fuzzy;
	intersection->refraction = sphere->refraction;
	intersection->normal = vec_normalize((intersection->p - sphere->pos) / (sphere->diameter / 2));
	if (dot(ray->direction, intersection->normal) > 0.0)
	{
		intersection->normal *= -1;
		intersection->front_face = false;
		//IN THE SPHR
	}
	else
	{
		intersection->front_face = true;
		//OUT THE SPHER
	}
	return (true);
}

//still seems a bit bugged.
bool	hit_plane(t_obj *plane, t_ray *ray, t_inter *intersection)
{
	double ddotn;

	ddotn = dot(ray->direction, plane->angle);

	if (ddotn == 0.0f)
		return (false);
	double t;
	t = dot(plane->pos - ray->origin, plane->angle) / ddotn;
	if (t <= RAY_T_MIN || t >= intersection->t)
		return (false);
	// printf ("plane time [%f]\n", t);
	intersection->t = t;
	intersection->obj = plane;
	intersection->ray = *ray;
	intersection->colour = plane->colour;
	intersection->fuzzy = plane->fuzzy;
	intersection->refraction = plane->refraction;
	intersection->p = ray_at_t(ray, intersection->t);
	intersection->normal = vec_normalize(plane->angle);
	intersection->material = plane->material;
	return (true);
}
