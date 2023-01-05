/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:13:59 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/05 03:42:28 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rt_error(char *error_msg)
{
	printf("%s\n", error_msg);
	exit (1);
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

bool	near_zero(t_vec vec)
{
	double near;

	near = 1e-8;
	if (fabs(vec[X]) < near && fabs(vec[Y]) < near && fabs(vec[Z]) < near)
		return (true);
	return (false);
}

double	reflectance(double cosine, double ref_idx)
{
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

t_vec	refract(const t_vec uv, const t_vec n, double etai_over_etat)
{
	double	cos_theta = fmin(dot(-uv, n), 1.0);
	t_vec	r_out_perp = etai_over_etat * (uv + cos_theta * n);
	t_vec	r_out_parallel = -sqrt(fabs(1.0 - vec_length_squared(r_out_perp))) * n;
	return (r_out_perp + r_out_parallel);
}

t_vec	reflect(const t_vec v, const t_vec n)
{
	return (v - 2 * dot(v, n) * n);
}

//random_unit_vector for diffuse random generation of vectors
t_vec	hemisphere(t_vec normal)
{
	t_vec random = vec_normalize(random_in_sphere());
	if (dot(random, normal) > 0.0)
		return (random);
	return (-random);
}

t_ray	scatter_ray(t_ray *ray, t_inter *intersection)
{
	t_vec	scatter_direction;
	t_ray	scattered;
	t_vec reflected;
	//lambertian (default)
	if (intersection->material == 0)
	{
		scatter_direction = intersection->p + hemisphere(intersection->normal);
		if (near_zero(scatter_direction))
			scatter_direction = intersection->normal;
		scattered = (t_ray){intersection->p, scatter_direction - intersection->p};
		// attenuation = intersection->colour;
	}
	//reflective 
	else if (intersection->material == 1)
	{
		reflected = reflect(vec_normalize(ray->direction), intersection->normal);
		scattered = (t_ray){intersection->p, reflected + intersection->fuzzy * vec_normalize(random_in_sphere())};
		// attenuation = intersection->colour;
	}
	//glass and water?
	else if (intersection->material == DIELECTRIC)
	{
		double	refraction_ratio;
		t_vec	unit_direction = vec_normalize(ray->direction);
		double	cos_theta = fmin(dot(-unit_direction, intersection->normal), 1.0);
		double	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		bool	cannot_refract = false;

		t_vec	direction;
		if (intersection->front_face)
			refraction_ratio = 1.0 / intersection->refraction;
		else
			refraction_ratio = intersection->refraction;
		if (refraction_ratio * sin_theta > 1.0)
			cannot_refract = true;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > ft_rand_double_normal(false, 0))
			direction = reflect(unit_direction, intersection->normal);		
		else
			direction = refract(unit_direction, intersection->normal, refraction_ratio);
		scattered = (t_ray){intersection->p, direction};
	}
	else
		return ((t_ray){(t_vec){-42}, (t_vec){-42}});

	return (scattered);
}

t_vec	get_light(t_raytracer *rt)
{
	t_obj	*obj;
	int i;
	i = -1;
	while (rt->objects[++i].type != LIGHT)
		;
	if (rt->objects[i].type == LIGHT)
		obj = &rt->objects[i];
	return (obj->pos);
}

//todo: colour with HSV
t_vec	ray_colour(t_ray *ray, t_raytracer *rt, int depth)
{
	t_vec	unit_direction = vec_normalize(ray->direction);
	t_inter	intersection;
	t_ray	scattered;
	intersection.t = RAY_T_MAX;
	intersection.material = 0;
	double	t;
	
	if (depth <= 0)
		return ((t_vec){0,0,0});
	ray_to_all_obj(ray, rt, &intersection);
	// if this if statement fails, all other things in intersection are SEGF material.
	if (intersection.t > 0.0f && intersection.t != RAY_T_MAX)
	{
		// t_vec random = intersection.p + intersection.normal + hemisphere(intersection.normal); // CAUSES DARK SHADOWS!
		t_vec random = intersection.p + hemisphere(intersection.normal);
		t_ray test;
		// intersection.material = 0;
		// test =  (t_ray){intersection.p, random - intersection.p};
		test = scatter_ray(ray, &intersection);
		
		// return (0.5f * ray_colour(&test, rt, depth - 1));
		t_vec light_dir = get_light(rt);
		
		double d;
		if (intersection.material != DIELECTRIC)
			d = fmax(dot(intersection.normal, -light_dir), 0.0f);
		else
			d = 1;
		return (d * intersection.colour * ray_colour(&test, rt, depth - 1));
		// return (0.5 * ray_colour(&(t_ray){intersection.p, random - intersection.p}, rt, depth - 1)); // normal render 
		// t_vec tmp = (vec_normalize(0.5 * intersection.colour)); //part of terrible colour
		// return ((0.5 * tmp) + (0.5 * ray_colour(&(t_ray){intersection.p, random - intersection.p}, rt, depth - 1))); //TERRIBLE COLOUR RENDER
		
		t_vec new;
		return (d * intersection.colour);
		new = vec_normalize(ray_at_t(ray, intersection.t) - (t_vec){0,0,-1}) + 1;
		return (0.5 * new);
	}
	t = 0.5 * (unit_direction[Y] + 1.0);
	return (((1.0 - t) * (t_vec){1.0, 1.0, 1.0}) + (t * (t_vec){0.5, 0.7, 1.0}));
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
			// col = vec_to_colour(vcol);
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
