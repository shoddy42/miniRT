/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/21 05:51:47 by wkonings      ########   odam.nl         */
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

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
//works on colour ranges from 0 to 1
uint32_t	vec_to_colour_normal(const t_vec vec)
{
	uint32_t colour;

	colour = 0;
	colour += (unsigned int)(255 * clamp(vec[R], 0.0, 0.999)) << 24;
	colour += (unsigned int)(255 * clamp(vec[G], 0.0, 0.999)) << 16;
	colour += (unsigned int)(255 * clamp(vec[B], 0.0, 0.999)) << 8;
	colour += 0x000000FF;
	// printf ("colour n?: %u \n", colour);
	return (colour);
}

//works on colour ranges from 0 to 255
uint32_t	vec_to_colour(const t_vec vec)
{
	uint32_t colour;

	colour = 0;
	colour += (unsigned int)(vec[R]) << 24;
	colour += (unsigned int)(vec[G]) << 16;
	colour += (unsigned int)(vec[B]) << 8;
	colour += 0x000000FF;
	// printf ("colour?: %u \n", colour);
	return (colour);
}

bool	ray_to_all_obj(t_ray *ray, t_raytracer *rt, t_inter *intersection)
{
	t_obj			*obj;
	int				i;
	double			closest;
	bool			hit;
	
	hit = false;
	i = -1;
	while (++i < rt->obj_idx)
	{
		obj = rt->objects + i;
		if (obj->type == SPHERE)
			if (hit_sphere(obj, ray, intersection))
				hit = true;
	}
	return (hit);
}

t_vec	ray_colour(t_ray *ray, t_raytracer *rt)
{
	t_vec	unit_direction = vec_normalize(ray->direction);
	t_inter	intersection;
	intersection.t = RAY_T_MAX;
	double	t;
	

	ray_to_all_obj(ray, rt, &intersection);
	// if this if statement fails, all other things in intersection are SEGF material.
	if (intersection.t > 0.0f && intersection.t != RAY_T_MAX)
	{
		t_vec new;
		// new = vec_normalize(ray_at_t(ray, intersection.t) - (t_vec){1,1,1});
		// new = vec_normalize(ray_at_t(ray, intersection.t) - intersection.obj->pos);
		// return (vec_to_colour_normal(0.5 * (new + 1)));
		return ((0.5 * (intersection.normal + (t_vec){1.0,1.0,1.0})));
	}
	t = 0.5 * (unit_direction[Y] + 1.0);
	return (((1.0 - t) * (t_vec){1.0, 1.0, 1.0}) + (t * (t_vec){0.5, 0.7, 1.0}));
}

void	first_frame(t_raytracer *rt)
{
	int x;
	int y;
	uint32_t col;
	t_vec	vcol;
	t_ray	ray;

	double u;
	double v;
	
	y = WINDOW_HEIGHT;
	col = 0;
	vcol = (t_vec){0.0, 0.0, 0.0};
	while (--y >= 0)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			u = (double)x / (double)WINDOW_WIDTH;
			v = (double)y / (double)WINDOW_HEIGHT;
			ray = get_ray(&rt->camera, u, v);
			vcol = ray_colour(&ray, rt);
			col = vec_to_colour_normal(vcol);
			mlx_put_pixel(rt->img, x, WINDOW_HEIGHT - y - 1, col);
		}
	}
}

void	cast_rays(t_raytracer *rt)
{
	int x;
	int y;
	int z;
	uint32_t col;
	// mlx_image_t *new;
	t_vec	vcol;
	t_ray	ray;

	double u;
	double v;
	// new = ft_calloc(1, sizeof(mlx_image_t));
	y = WINDOW_HEIGHT;
	col = 0;
	vcol = (t_vec){0.0, 0.0, 0.0};
	while (--y >= 0)
	{
		// printf ("Lines remaining [%i]\n", WINDOW_HEIGHT - y);
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			z = -1;
			while (++z < MAX_SAMPLES)
			{
				u = ((double)x + drand48()) / (double)WINDOW_WIDTH;
				v = ((double)y + drand48()) / (double)WINDOW_HEIGHT;
				//get_ray function
				// ray.origin = rt->camera.pos;
				// ray.direction = rt->camera.low_left_corner + (u * rt->camera.horizontal) + (v * rt->camera.vertical) - rt->camera.pos;
				ray = get_ray(&rt->camera, u, v);
				// col = vec_to_colour((t_vec){(double)x / (double)WINDOW_WIDTH, (double)y / (double)WINDOW_HEIGHT, (double)0.2});
				// col = vec_to_colour(ray_colour(&ray));
				vcol += ray_colour(&ray, rt);
			}
			vcol /= (double)z;
			col = vec_to_colour_normal(vcol);
			mlx_put_pixel(rt->img, x, WINDOW_HEIGHT - y - 1, col);
		}
	}
}

int	main(int ac, char **av)
{
	t_raytracer	rt;
	unsigned int wait = 0;
	ft_bzero(&rt, sizeof(t_raytracer));
	if (ac < 2)
		rt_error("No input");
	if (ac > 3)
		rt_error("Too many inputs.");
	init_struct(&rt, av);
	// first_frame(&rt);
	// while (++wait < UINT32_MAX)
		// ;
	cast_rays(&rt);
	// draw_vec(rt.map, &rt);
	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);
	return (0);
}
