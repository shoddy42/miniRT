/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 04:27:32 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 23:16:06 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	update_camera(t_raytracer *rt)
{
	t_camera *cam;

	cam = &rt->camera;

	double	theta;
	double	h;
	
	printf ("mlx w: [%i] h: [%i] ratio = [%i]\n", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH / WINDOW_HEIGHT);

	theta = deg_to_rad(cam->fov);
	h = tan(theta/2);
	cam->view_height = 2.0 * h;
	cam->view_width = cam->aspect_ratio * cam->view_height;

	cam->w = vec_normalize(cam->pos - cam->direction);
	cam->u = vec_normalize(cross(cam->up, cam->w));
	cam->v = cross(cam->w, cam->u);

	cam->horizontal = cam->focus_dist * cam->view_width * cam->u;
	cam->vertical = cam->focus_dist * cam->view_height * cam->v;
	rt->camera.low_left_corner = rt->camera.pos - (rt->camera.horizontal / 2) - (rt->camera.vertical/2) - (cam->focus_dist * cam->w);
	cam->lens_radius = cam->aperature / 2;
	cam->focus_dist = vec_length((cam->pos - cam->direction));
}
