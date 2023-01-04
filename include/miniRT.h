/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 18:26:03 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/04 01:51:48 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
// currently forced to stay at 2:1 aspect ratio
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 800

# define MAX_WINDOW_WIDTH 2560 //todo: enable these.
# define MAX_WINDOW_HEIGHT 1440
# define MIN_WINDOW_WIDTH 80
# define MIN_WINDOW_HEIGHT 40

# define RAY_T_MIN 0.001f
# define RAY_T_MAX 1.0e30f
# define RAY_MAX_DEPTH 50
# define BOUNCES 5
# define PI 3.1415926535897932385
# define ENHANCE_SAMPLES 10
# define MAX_SAMPLES 250
# define FOV 90
# include "vector.h"
# include "../mlx/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>

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

typedef struct s_material
{
	t_vec	colour;
	t_vec	attenuation;
	t_vec	reflectance;
	float	fuzzy;
}	t_mat;

typedef struct s_object
{
	t_obj_type	type;

	t_vec		pos;
	t_vec		angle;
	t_vec		colour;
	double		diameter;
	double		height;

	int			material;
	float		fuzzy;

	double		fov; //for camera only.
}	t_obj;


typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;	
}	t_ray;


typedef struct s_inter
{
	double	t;
	t_ray	ray;
	t_obj	*obj;
	t_vec	colour;
	t_vec	p; // the position at which we hit
	t_vec	normal; //the normal 

	int		material;
	float	fuzzy;

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
	t_vec		**last_frame;
	mlx_image_t	*img;
	t_vector	**map;
	t_camera	camera;
	t_obj		*objects;
	int			obj_idx;
	
	int			total_samples;
	bool		key_pressed;
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
void	hook(void *param);
void	enhance(t_raytracer *rt);
void	first_frame(t_raytracer *rt);
double	rad_to_deg(const double a);
double	deg_to_rad(const double a);
bool	hit_plane(t_obj *plane, t_ray *ray, t_inter *intersection);
#endif