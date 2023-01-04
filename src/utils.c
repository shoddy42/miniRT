/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 22:48:25 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 22:48:34 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	deg_to_rad(const double a)
{
	return (a / 360.0f * 2.0f * M_PI);
}

double	rad_to_deg(const double a)
{
	return (a / (2.0f * M_PI) * 360.0f);
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

	while (true)
	{
		target = (t_vec){	ft_rand_double_normal(true, 0),
							ft_rand_double_normal(true, 0),
							ft_rand_double_normal(true, 0)};
		if (vec_length_squared(target) < 1)
			return (target);
	}
	return ((t_vec){0,0,0});
}

t_vec	random_in_disc(void)
{
	t_vec	target;

	while (true)
	{
		target = (t_vec){	ft_rand_double_normal(true, 0),
							ft_rand_double_normal(true, 0),
							0};
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