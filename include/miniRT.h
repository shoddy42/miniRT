/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:26:03 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/15 18:19:01 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define FOV 90
# include "mlx/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define YELLOW	"\1\33[38;5;220m\2"
# define BLACK	"\1\33[38;5;232m\2"
# define ORANGE	"\1\33[38;5;202m\2"
# define RED	"\1\33[38;5;196m\2"
# define PINK	"\1\33[38;5;198m\2"
# define GREEN	"\1\33[38;5;28m\2"
# define BLUE	"\1\33[38;5;33m\2"
# define L_BLUE	"\1\33[38;5;69m\2"
# define D_BLUE	"\1\33[38;5;21m\2"
# define GREY	"\1\33[38;5;242m\2"
# define PURPLE	"\1\33[38;5;92m\2"
# define VIOLET	"\1\33[38;5;183m\2"
# define RESET	"\1\33[0m\2"
# define END	"\1\33[0m\2\3"
typedef double	t_vec __attribute__ ((vector_size (4 * sizeof(double))));

typedef enum e_vecnum
{
	X,
	Y,
	Z,
	W
}	t_vecnum;

typedef enum e_vec_colour
{
	R,
	G,
	B,
	A
}	t_vec_colour;

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
	CAMERA,
	LIGHT,
	AMBIENT,
}	t_obj_type;

typedef struct s_sphere
{
	t_vec		pos;
	float		diameter;
	t_vec		colour;
}	t_sphere;


typedef union u_base
{
	t_sphere	sphere;
}	t_base;

typedef struct s_object
{
	t_obj_type	type;
	t_base		shape;
	t_vec		pos;
	t_vec		colour;
	t_vec		angle;
	float		diameter;
	float		height;

	float		fov;
}	t_obj;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	t_vec	pos;
	
}	t_ray;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	direction;
	
	float	view_height;
	float	view_width;
	float	focal_length;
	t_vec	low_left_corner;
	t_vec	horizontal;
	t_vec	vertical;
	float	fov;
}	t_camera;

typedef struct s_raytracer
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vector	**map;
	t_camera	camera;
	t_obj		*objects;
	int			obj_idx;
	
	char		*title;
}				t_raytracer;

void	keyhook(mlx_key_data_t keydata, void	*param);
bool	open_scene(char **av, t_raytracer *rt);
void	rt_error(char *error_msg);



bool	parse_sphere(char *line, t_raytracer *rt, int idx);
bool	parse_plane(char *line, t_raytracer *rt, int idx);
bool	parse_cylinder(char *line, t_raytracer *rt, int idx);
bool	parse_camera(char *line, t_raytracer *rt, int idx);

char	*set_rgb(char *line, t_obj *obj);
char	*set_pos(char *line, t_obj *obj);
char	*set_orientation(char *line, t_obj *obj);


#endif