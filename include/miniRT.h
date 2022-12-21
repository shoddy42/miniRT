/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:26:03 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/21 05:51:32 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 800
# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f
# define PI 3.1415926535897932385
# define MAX_SAMPLES 10
# define FOV 90
# include "vector.h"
# include "../mlx/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
// # include <stdlib.h>
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

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CAMERA,
	LIGHT,
	AMBIENT,
	ERROR,
}	t_obj_type;

typedef struct s_object
{
	t_obj_type	type;

	t_vec		pos;
	t_vec		angle;
	t_vec		colour;
	double		diameter;
	double		height;

	double		fov; //for camera only.
}	t_obj;


typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	t_vec	pos;
	
}	t_ray;


typedef struct s_inter
{
	double	t;
	t_ray	ray;
	t_obj	*obj;
	t_vec	colour;
	t_vec	p; // the position at which we hit
	t_vec	normal; //the normal 
	bool	front_face;
}	t_inter;

typedef struct s_camera
{
	t_vec	pos; // should rename to origin
	t_vec	direction;
	
	double	aspect_ratio;
	double	view_height;
	double	view_width;
	double	focal_length;
	t_vec	low_left_corner;
	t_vec	horizontal;
	t_vec	vertical;
	double	fov;
}	t_camera;

typedef struct s_raytracer
{
	mlx_t		*mlx;
	double	**last_frame;
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


// vector lib
double	vec_length(t_vec vec);
double	vec_length_squared(t_vec vec);
double	sqr(double x);
double	dot(t_vec a, t_vec b);
t_vec	cross(t_vec a, t_vec b);
t_vec	vec_normalize(t_vec vec);

//intersections
bool	hit_sphere(t_obj *sphere, t_ray *ray, t_inter *intersection);

//rays
t_vec	ray_at_t(t_ray *ray, const double t);

//unsorted
void	cast_rays(t_raytracer *rt);
t_ray	get_ray(t_camera *cam, double u, double v);
void	update_camera(t_raytracer *rt);
#endif