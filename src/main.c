/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/14 19:55:55 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rt_error(char *error_msg)
{
	printf("%s\n", error_msg);
	exit (1);
}

void	init_struct(t_raytracer *rt, char **av)
{
	rt->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, ft_strjoin("miniRT - ", av[1]), true);
	if (!rt->mlx)
		exit(1);
	
	rt->img = mlx_new_image(rt->mlx, rt->mlx->width, rt->mlx->height);
	if (!rt->img)
		rt_error("Image construction failed");
	open_scene(av, rt);
	mlx_image_to_window(rt->mlx, rt->img, 0, 0);
	// mlx_scroll_hook(rt->mlx, &scrollhook, rt);
	mlx_key_hook(rt->mlx, &keyhook, rt);
	// mlx_resize_hook(rt->mlx, &resize, rt);
	// mlx_loop_hook(rt->mlx, &hook, rt);
	// draw_vec(rt->map, rt);
}

int	main(int ac, char **av)
{
	t_raytracer	rt;
	
	ft_bzero(&rt, sizeof(t_raytracer));
	if (ac < 2)
		rt_error("No input");
	if (ac > 3)
		rt_error("Too many inputs.");
	init_struct(&rt, av);
	// draw_vec(rt.map, &rt);
	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);
	return (0);
}
