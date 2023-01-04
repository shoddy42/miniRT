/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:46:37 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 21:53:48 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	hook(void *param)
{
	t_raytracer	*rt;

	rt = param;
	if (rt->key_pressed == true)
		return ;
	// printf ("executing time %f\n", mlx_get_time());
	// cast_rays(rt);
	rt = param;
}

void	clear_frames(t_raytracer *rt)
{
	int	x;
	int y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			rt->last_frame[y][x] = (t_vec){0,0,0};
	}
	rt->total_samples = 0;
}

void	keyhook(mlx_key_data_t keydata, void	*param)
{
	t_raytracer	*rt;
	double	magnitude;

	rt = param;
	magnitude = 1;
	rt->key_pressed = true;
	if (keydata.key == MLX_KEY_ESCAPE || mlx_is_key_down(rt->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(rt->mlx);
		return ;
	}
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_R)
	{
		enhance(rt);
		return ;
	}
	if (mlx_is_key_down(rt->mlx, MLX_KEY_LEFT_SHIFT))
		magnitude *= 10;
	if (keydata.key == MLX_KEY_A)
		rt->camera.pos[X] -= 0.1;
	if (keydata.key == MLX_KEY_D)
		rt->camera.pos[X] += 0.1;
	if (keydata.key == MLX_KEY_W)
		rt->camera.pos[Z] -= 0.1;
	if (keydata.key == MLX_KEY_S)
		rt->camera.pos[Z] += 0.1;
	if (keydata.key == MLX_KEY_Q)
		rt->camera.pos[Y] -= 0.1;
	if (keydata.key == MLX_KEY_E)
		rt->camera.pos[Y] += 0.1;
	if (keydata.key == MLX_KEY_UP)
		rt->camera.direction[Y] += 0.1;
	if (keydata.key == MLX_KEY_DOWN)
		rt->camera.direction[Y] -= 0.1;
	if (keydata.key == MLX_KEY_LEFT)
		rt->camera.direction[X] -= 0.1;
	if (keydata.key == MLX_KEY_RIGHT)
		rt->camera.direction[X] += 0.1;
	clear_frames(rt);
	update_camera(rt);
	first_frame(rt);

	
	// ft_bzero(rt->last_frame, WINDOW_WIDTH * WINDOW_HEIGHT);
	// ft_bzero(rt->img->pixels, rt->img->width * rt->img->height * sizeof(uint32_t));
	// cast_rays(rt);
	// update_camera(rt);
}
