/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:46:37 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/21 01:32:47 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	keyhook(mlx_key_data_t keydata, void	*param)
{
	t_raytracer	*rt;
	double	magnitude;

	rt = param;
	magnitude = 1;
	if (mlx_is_key_down(rt->mlx, MLX_KEY_LEFT_SHIFT))
		magnitude *= 10;
	if (mlx_is_key_down(rt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(rt->mlx);
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_A)
		rt->camera.pos[X] -= 0.1;
	if (keydata.key == MLX_KEY_D)
		rt->camera.pos[X] += 0.1;
	if (keydata.key == MLX_KEY_W)
		rt->camera.pos[Y] -= 0.1;
	if (keydata.key == MLX_KEY_S)
		rt->camera.pos[Y] += 0.1;
	cast_rays(rt);
}
