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
t_ray	get_ray(t_camera *cam, double s, double t)
{
	t_ray	ray;
	t_vec	random;
	
	t_vec	offset;

	if (cam->dof)
	{
		random = cam->lens_radius * random_in_disc();
		offset = cam->u * random[X] + cam->v * random[Y];
	}
	else
		offset = (t_vec){0,0,0};
	ray.origin = cam->pos + offset;
	ray.direction = cam->low_left_corner + (s * cam->horizontal) + (t * cam->vertical) - cam->pos - offset;
	return (ray);
}