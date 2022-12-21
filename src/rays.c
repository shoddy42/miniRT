	/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 22:05:06 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/20 07:00:53 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec	ray_at_t(t_ray *ray, const double t)
{
	return (ray->origin + (ray->direction * t));
}

//wtf?
t_ray	get_ray(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.origin = cam->pos;
	ray.direction = cam->low_left_corner + (u * cam->horizontal) + (v * cam->vertical) - cam->pos;
	return (ray);
}