/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/22 11:28:35 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rt_error(char *error_msg)
{
	printf("%s\n", error_msg);
	exit (1);
}

//todo: add whole random suite to libft.
//todo: add the whole vectorlib bs to libft.
double ft_rand_double(bool allow_negative, int init)
{
	static int seed;
	
	if (init != 0)
		seed = init;
	seed = (1103515245 * seed + 12345) % (int)pow(2, 31);
	if (allow_negative == false && seed < 0)
		return ((double)seed * -1);
	return ((double)seed);
}

/**
 * @brief Generates a random number 
 * 
 * @param allow_negative whether returning a negative number is allowed or not.
 * @param init 
 * @return double 
 */
double ft_rand_double_normal(bool allow_negative, int init)
{
	static int	seed;
	double		ret;
	
	if (init != 0)
		seed = init;
	seed = (1103515245 * seed + 12345) % (int)pow(2, 31);
	ret = (double)seed / RAND_MAX;
	if (allow_negative ==false && ret < 0)
		ret *= -1;
	return (ret);
}

t_vec	random_in_sphere(void)
{
	t_vec	target;
	int		i;

	i = 0;
	while (++i < 1000)
	{
		target = (t_vec){ ft_rand_double_normal(true, 0),
						ft_rand_double_normal(true, 0),
						ft_rand_double_normal(true, 0)};
		if (vec_length_squared(target) < 1)
			return (target);
	}
	return ((t_vec){0,0,0});
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
uint32_t	vec_to_colour_normal(t_vec vec, t_raytracer *rt)
{
	uint32_t	colour;

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
		if (obj->type == PLANE)
			if (hit_plane(obj, ray, intersection))
				hit = true;
	}
	return (hit);
}

t_vec	hemisphere(t_vec normal)
{
	t_vec random = vec_normalize(random_in_sphere());
	if (dot(random, normal) > 0.0)
		return (random);
	return (-random);
}

t_vec	ray_colour(t_ray *ray, t_raytracer *rt, int depth)
{
	t_vec	unit_direction = vec_normalize(ray->direction);
	t_inter	intersection;
	intersection.t = RAY_T_MAX;
	double	t;
	
	if (depth <= 0)
		return ((t_vec){0,0,0});
	ray_to_all_obj(ray, rt, &intersection);
	// if this if statement fails, all other things in intersection are SEGF material.
	if (intersection.t > 0.0f && intersection.t != RAY_T_MAX)
	{
		//for recursive bouncing of rays!
		t_vec random = intersection.p + intersection.normal + hemisphere(intersection.normal);
		return ((0.5 * ray_colour(&(t_ray){intersection.p, random - intersection.p, (t_vec){0}}, rt, depth - 1)) + (0.5 * intersection.colour));
		
		//backup bad render
		return ((0.5 * (intersection.normal + (t_vec){1.0,1.0,1.0})));
	}
	t = 0.5 * (unit_direction[Y] + 1.0);
	return (((1.0 - t) * (t_vec){1.0, 1.0, 1.0}) + (t * (t_vec){0.5, 0.7, 1.0}));
	// return (((1.0 - t) * (t_vec){1.0, 1.0, 1.0}) + (t * (t_vec){1.0, 0.7, 0.3}));
	// return ((t_vec){0,0,0});
}

// quickly does the first frame only.
void	first_frame(t_raytracer *rt)
{
	int x;
	int y;
	uint32_t col;
	t_vec	vcol;
	t_ray	ray;

	double u;
	double v;
	double scale;
	
	y = WINDOW_HEIGHT;
	col = 0;
	vcol = (t_vec){0.0, 0.0, 0.0};
	rt->total_samples = 1;
	scale = 1.0 / rt->total_samples;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			u = (double)x / (double)WINDOW_WIDTH;
			v = (double)y / (double)WINDOW_HEIGHT;
			ray = get_ray(&rt->camera, u, v);
			vcol = ray_colour(&ray, rt, RAY_MAX_DEPTH);
			rt->last_frame[y][x] = vcol;
			vcol[R] = sqrt(scale * vcol[R]);
			vcol[G] = sqrt(scale * vcol[G]);
			vcol[B] = sqrt(scale * vcol[B]);
			col = vec_to_colour_normal(vcol, rt);
			mlx_put_pixel(rt->img, x, WINDOW_HEIGHT - y - 1, col);
		}
	}
	// printf ("FIRST last pixel [%f][%f][%f]  col [%u]\n", vcol[X], vcol[Y], vcol[Z], col);
	// printf ("FIRST ? [%f][%f][%f]\n", rt->last_frame[0][WINDOW_WIDTH - 1][X], rt->last_frame[0][WINDOW_WIDTH - 1][Y], rt->last_frame[0][WINDOW_WIDTH - 1][Z]);
}

// handles anti-aliasing.
void	enhance(t_raytracer *rt)
{
	int x;
	int y;
	int samples;
	uint32_t col;
	t_vec	vcol;
	t_ray	ray;

	double u;
	double v;
	y = WINDOW_HEIGHT;
	col = 0;
	samples = -1;
	while (++samples < ENHANCE_SAMPLES && rt->total_samples < MAX_SAMPLES)
	{
		printf ("remaining [%i]\n", ENHANCE_SAMPLES - samples);
		y = WINDOW_HEIGHT;
		while (--y >= 0)
		{
			x = -1;
			while (++x < WINDOW_WIDTH)
			{
				u = ((double)x + ft_rand_double_normal(false, 0)) / (double)WINDOW_WIDTH;
				v = ((double)y + ft_rand_double_normal(false, 0)) / (double)WINDOW_HEIGHT;
				ray = get_ray(&rt->camera, u, v);
				rt->last_frame[y][x] += ray_colour(&ray, rt, RAY_MAX_DEPTH);
			}
		}
	}
	printf ("???? [%f][%f][%f]\n", rt->last_frame[0][WINDOW_WIDTH - 1][X], rt->last_frame[0][WINDOW_WIDTH - 1][Y], rt->last_frame[0][WINDOW_WIDTH - 1][Z]);

	double		scale;
	y = WINDOW_HEIGHT;
	rt->total_samples += samples;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			// get colour of all frames and even them out, then adjusts for gamma
			scale = 1.0 / rt->total_samples;
			vcol = rt->last_frame[y][x];
			vcol[R] = sqrt(scale * vcol[R]);
			vcol[G] = sqrt(scale * vcol[G]);
			vcol[B] = sqrt(scale * vcol[B]);
			col = vec_to_colour_normal(vcol, rt);
			mlx_put_pixel(rt->img, x, WINDOW_HEIGHT - y - 1, col);
		}
	}
	// printf ("last pixel [%f][%f][%f] col: [%u]\n", vcol[X], vcol[Y], vcol[Z], col);
	// printf ("? [%f][%f][%f]\n", rt->last_frame[0][WINDOW_WIDTH - 1][X], rt->last_frame[0][WINDOW_WIDTH - 1][Y], rt->last_frame[0][WINDOW_WIDTH - 1][Z]);
	printf ("ENHANCED! TOTAL SAMPLES: %i\n", rt->total_samples);
}

void	init_struct(t_raytracer *rt, char **av)
{
	char *title;

	open_scene(av, rt);
	title = ft_strjoin("miniRT - ", av[1]);
	rt->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, title, false);
	if (!rt->mlx)
		exit(1);
	rt->img = mlx_new_image(rt->mlx, rt->mlx->width, rt->mlx->height);
	if (!rt->img)
		rt_error("Image construction failed");
	mlx_image_to_window(rt->mlx, rt->img, 0, 0);
	mlx_key_hook(rt->mlx, &keyhook, rt);
	mlx_loop_hook(rt->mlx, &hook, rt);
	free (title);
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
	rt.last_frame = ft_calloc(WINDOW_HEIGHT + 1, (sizeof (t_vec *)));
	int i = -1;
	while (++i < WINDOW_HEIGHT)
		rt.last_frame[i] = ft_calloc(WINDOW_WIDTH + 1, sizeof(t_vec));
	first_frame(&rt);
	mlx_loop(rt.mlx);
	mlx_delete_image(rt.mlx, rt.img);
	mlx_terminate(rt.mlx);
	return (0);
}
