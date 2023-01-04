/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 04:27:32 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 02:05:41 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	update_camera(t_raytracer *rt)
{
	t_camera *cam;

	cam = &rt->camera;
	
	double theta;
	double h;
	double	aspect_ratio;
	// aspect_ratio = rt->mlx->width / rt->mlx->height;

	aspect_ratio = 2/1;
	theta = deg_to_rad(rt->camera.fov);
	h = tan(theta/2);

	rt->camera.view_height = 2.0 * h;
	rt->camera.view_width = aspect_ratio * rt->camera.view_height;
	rt->camera.focal_length = 1.0;

	rt->camera.horizontal = (t_vec){rt->camera.view_width, 0, 0};
	rt->camera.vertical = (t_vec){0, rt->camera.view_height, 0};
	rt->camera.low_left_corner = rt->camera.pos - (rt->camera.horizontal / 2) - (rt->camera.vertical/2) - (t_vec){0,0,rt->camera.focal_length};
}
