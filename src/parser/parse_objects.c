/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_objects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 19:44:21 by wkonings      #+#    #+#                 */
/*   Updated: 2023/01/18 17:50:18 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool	parse_cylinder(char *line, t_raytracer *rt, int idx)
{
	rt->objects[idx].type = CYLINDER;
	printf (PURPLE "parsing cylinder! [%s] idx [%i]\n", line, idx);
	line = set_pos(line, &rt->objects[idx]);
	line = set_orientation(line, &rt->objects[idx]);
	rt->objects[idx].diameter = ft_atod(line);
	while (*line && (ft_isdigit(*line) || *line == '.'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	rt->objects[idx].height = ft_atod(line);
	while (*line && (ft_isdigit(*line) || *line == '.'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	line = set_rgb(line, &rt->objects[idx]);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	printf ("angle?: [%f][%f][%f]\n", rt->objects[idx].angle[X], rt->objects[idx].angle[Y], rt->objects[idx].angle[Z]);
	printf ("diameter: %f\n", rt->objects[idx].diameter);
	printf ("height: %f\n", rt->objects[idx].height);
	printf ("colour?: [%f][%f][%f]\n", rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	printf (END "\n");
	//todo: check for additional input that isnt needed?
	return (true);
}

t_vec	col_scale(t_vec original)
{
	t_vec	colour;

	colour = original / 255;
	return (colour);
}

bool	parse_sphere(char *line, t_raytracer *rt, int idx)
{
	rt->objects[idx].type = SPHERE;
	printf (BLUE "parsing sphere! [%s] idx [%i]\n", line, idx);
	line = set_pos(line, &rt->objects[idx]);
	// rt->objects[idx].colour = ft_calloc(1, sizeof(t_vec));
	rt->objects[idx].colour[R] = 42;
	rt->objects[idx].diameter = ft_atod(line);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	line = set_rgb(line, &rt->objects[idx]);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	printf ("diameter: %f\n", rt->objects[idx].diameter);
	printf ("colour?: [%f][%f][%f]\n", rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	printf (END "\n");
	// normalizes colour between 0.0 and 1.0
	rt->objects[idx].colour = col_scale(rt->objects[idx].colour);
	printf (RED "colour?: [%f][%f][%f]\n" END, rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	//todo: check for additional input that isnt needed?
	// BONUS ZONE
	rt->objects[idx].material = ft_atoi(line);
	while (*line && (ft_isdigit(*line) || *line == '.'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	printf (ORANGE"mat = %i\n" END, rt->objects[idx].material);
	rt->objects[idx].fuzzy = ft_atof(line);
	printf (ORANGE"fuzz = %f\n" END, rt->objects[idx].fuzzy);
	if (rt->objects[idx].material == DIELECTRIC)
		rt->objects[idx].refraction = rt->objects[idx].fuzzy; 
	return (true);
}

bool	parse_plane(char *line, t_raytracer *rt, int idx)
{
	rt->objects[idx].type = PLANE;
	printf (VIOLET "parsing plane! [%s] idx [%i]\n", line, idx);
	line = set_pos(line, &rt->objects[idx]);
	line = set_orientation(line, &rt->objects[idx]);
	line = set_rgb(line, &rt->objects[idx]);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	printf ("angle?: [%f][%f][%f]\n", rt->objects[idx].angle[X], rt->objects[idx].angle[Y], rt->objects[idx].angle[Z]);
	printf ("colour?: [%f][%f][%f]\n", rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	printf (END "\n");
	//todo: check for additional input that isnt needed?	
	return (true);
}


//todo: make this its own class and not use objects.idx at all anymore.
bool	parse_camera(char *line, t_raytracer *rt, int idx)
{
	t_camera *cam;

	rt->objects[idx].type = CAMERA;
	printf (YELLOW "parsing camera! [%s] idx [%i]\n", line, idx);
	line = set_pos(line, &rt->objects[idx]);
	printf (YELLOW "parsing camera! [%s] idx [%i]\n", line, idx);
	line = set_orientation(line, &rt->objects[idx]);
	rt->objects[idx].fov = ft_atod(line);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	printf ("angle?: [%f][%f][%f]\n", rt->objects[idx].angle[X], rt->objects[idx].angle[Y], rt->objects[idx].angle[Z]);
	printf ("FOV?: [%f]", rt->objects[idx].fov);
	printf (END "\n");

	cam = &rt->camera;

	cam->pos = rt->objects[idx].pos;
	cam->direction = rt->objects[idx].angle;
	cam->fov = rt->objects[idx].fov;

	cam->aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
	cam->up = (t_vec){0,1,0};

	// cam->focus_dist = 1;
	cam->aperature = 2.0;
	cam->lens_radius = cam->aperature / 2;
	cam->focus_dist = vec_length((cam->pos - cam->direction));
	
	update_camera(rt);

	//todo: check for additional input that isnt needed?	
	return (true);
}

bool	parse_light(char *line, t_raytracer *rt, int idx)
{
	rt->objects[idx].type = LIGHT;
	printf (VIOLET "parsing light! [%s] idx [%i]\n", line, idx);
	line = set_pos(line, &rt->objects[idx]);
	rt->objects[idx].brightness = ft_atod(line);
	printf ("brightness?: [%f]\n", rt->objects[idx].brightness);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	line = set_rgb(line, &rt->objects[idx]);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	// normalizes colour between 0.0 and 1.0
	rt->objects[idx].colour = col_scale(rt->objects[idx].colour);
	printf ("colour?: [%f][%f][%f]\n" END, rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	//todo: check for additional input that isnt needed?
	// BONUS ZONE
	return (true);
}

bool	parse_ambient(char *line, t_raytracer *rt, int idx)
{
	rt->objects[idx].type = AMBIENT;
	printf (ORANGE "parsing ambient! [%s] idx [%i]\n", line, idx);
	rt->objects[idx].brightness = ft_atod(line);
	printf ("brightness?: [%f]\n", rt->objects[idx].brightness);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	line = set_rgb(line, &rt->objects[idx]);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	rt->objects[idx].colour /= 255;
	rt->ambient = &rt->objects[idx];
	// normalizes colour between 0.0 and 1.0
	// rt->objects[idx].colour = col_scale(rt->objects[idx].colour);
	// printf ("colour?: [%f][%f][%f]\n" END, rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	//todo: check for additional input that isnt needed?
	// BONUS ZONE
	return (true);
}