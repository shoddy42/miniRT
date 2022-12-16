/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/16 21:59:08 by root          ########   odam.nl         */
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
	char *title;

	open_scene(av, rt);
	// title = ft_strjoin("miniRT - ", av[1]);
	rt->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "title", true);
	if (!rt->mlx)
		exit(1);
	rt->img = mlx_new_image(rt->mlx, rt->mlx->width, rt->mlx->height);
	if (!rt->img)
		rt_error("Image construction failed");
	mlx_image_to_window(rt->mlx, rt->img, 0, 0);
	mlx_key_hook(rt->mlx, &keyhook, rt);

	// free (title);
}

uint32_t	vec_to_colour(const t_vec *vec)
{
	uint32_t colour;
	double	col;

	colour = 0;
	col = 0;
	// col = vec[X];
	// printf ("huh: [%f]\n", vec[X]);
	return (colour);
}

// t_vec	ray_colour(const t_ray *ray)
// {
// 	t_vec	unit_direction = ray->direction;
// 	double	t = 0.5 * (unit_direction[Y] + 1.0);
// 	return (((1.0 - t) * (t_vec){1.0, 1.0, 1.0}) + (t * (t_vec){0.5, 0.7, 1.0}));
// }

uint32_t	find_obj(t_raytracer *rt, t_ray *ray)
{
	int	i;

	i = -1;
	while (++i < rt->obj_idx)
	{
		if (ray->pos[X] == rt->objects[i].pos[X] && ray->pos[X] != 0)
		{
			// printf ("X HIT!\n");
			return (0xCCC22CCC);
		}
		if (ray->pos[Y] == rt->objects[i].pos[Y])
		{
			// printf ("Y HIT!\n");
			return (0xEEEEEEEE);
		}
		if (ray->pos[Z] == rt->objects[i].pos[Z])
		{
			// printf ("Z HIT!\n");
			return (0xAAAAAAAA);
		}
	}
	return (0xFFFFFFFF);
}

uint32_t	yeet_ray(t_raytracer *rt, t_ray *ray)
{
	ray->direction = rt->camera.direction;
	ray->origin = rt->camera.pos;
	ray->pos = ray->origin;

	// printf ("yeeting rays!\n");
	while (ray->pos[X] < 100 && ray->pos[Y] < 100 && ray->pos[Z] < 100)
	{
		if (find_obj(rt, ray) != 0xAAAAAAAA)
			return (find_obj(rt, ray));
		ray->pos += ray->direction;
	}
	return (0x00000000);
}

void	cast_rays(t_raytracer *rt)
{
	int x;
	int y;
	uint32_t col;
	t_ray	ray;

	double u;
	double v;
	y = -1;
	
	// printf ("casting rays!");
	// low_left_corner = 1;
	while (++y < WINDOW_HEIGHT)
	{
		// printf ("Lines remaining [%i]\n", WINDOW_HEIGHT - y);
		x = -1;
		while (++x <= WINDOW_WIDTH)
		{
			// u = (double)x / (double)WINDOW_WIDTH -1;
			// v = (double)y / (double)WINDOW_HEIGHT -1;
			// ray.origin = rt->camera.pos;
			// ray.direction = rt->camera.low_left_corner + (u * rt->camera.horizontal) + (v * rt->camera.vertical) - rt->camera.pos;
			// col = 0xFFFFFFFF;

			// if (x >= 200 && x <= 400)
			// 	col = 0xAAAAAAAA;
			// col = ray_colour(&ray);
			col = yeet_ray(rt, &ray);
			mlx_put_pixel(rt->img, x, y, col);
		}
	}

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
	cast_rays(&rt);
	// draw_vec(rt.map, &rt);
	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);
	return (0);
}
