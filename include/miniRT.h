/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:26:03 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/14 19:52:22 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# include "mlx/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef double	t_vec __attribute__ ((vector_size (4 * sizeof(double))));

typedef enum e_vecnum
{
	X,
	Y,
	Z,
	W
}	t_vecnum;

typedef struct s_vector
{
	t_vec		vec;
	uint32_t	colour;
}	t_vector;

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER,
}	t_obj_type;

typedef struct s_object
{
	t_obj_type type;
	// union	base;
}	t_obj;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	
}	t_ray;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	direction;
}	t_camera;

typedef struct s_raytracer
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vector	**map;
	t_camera	camera;
	t_obj		*objects;
	
	char		*title;
}				t_raytracer;

void	keyhook(mlx_key_data_t keydata, void	*param);
bool	open_scene(char **av, t_raytracer *rt);
void	rt_error(char *error_msg);



bool	parse_sphere(char *line, t_raytracer *rt);


#endif