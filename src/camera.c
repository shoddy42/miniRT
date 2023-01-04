/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 04:27:32 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 22:15:52 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	update_camera(t_raytracer *rt)
{
	t_camera *cam;

	cam = &rt->camera;
	
	double	theta;
	double	h;
	double	aspect_ratio;
	t_vec	w;
	t_vec	u;
	t_vec	v;
	
	printf ("mlx w: [%i] h: [%i] ratio = [%i]\n", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH / WINDOW_HEIGHT);
	aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;

	theta = deg_to_rad(cam->fov);
	h = tan(theta/2);
	cam->view_height = 2.0 * h;
	cam->view_width = cam->aspect_ratio * cam->view_height;

	w = vec_normalize(cam->pos - cam->direction);
	u = vec_normalize(cross(cam->up, w));
	v = cross(w, u);

	cam->horizontal = cam->view_width * u;
	cam->vertical = cam->view_height * v;
	rt->camera.low_left_corner = rt->camera.pos - (rt->camera.horizontal / 2) - (rt->camera.vertical/2) - w;
}
