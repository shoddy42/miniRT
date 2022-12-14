/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:46:37 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/14 19:55:53 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	keyhook(mlx_key_data_t keydata, void	*param)
{
	t_raytracer	*rt;
	double	magnitude;

	rt = param;
	magnitude = 1;
	if (mlx_is_key_down(rt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(rt->mlx);
	if (keydata.action == MLX_RELEASE)
		return ;
	// if (mlx_is_key_down(rt->mlx, MLX_KEY_LEFT_SHIFT))
	// 	magnitude *= 10;
	// transpose(rt, magnitude);
	// scale(rt, magnitude);
	// angle(rt, magnitude);
	// setting_toggles(rt);
	// if (rt->settings->scale < 1)
	// 	rt->settings->scale = 1;
}
