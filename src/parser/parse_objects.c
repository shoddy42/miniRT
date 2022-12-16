/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_objects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 19:44:21 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/16 22:05:51 by root          ########   odam.nl         */
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

bool	parse_sphere(char *line, t_raytracer *rt, int idx)
{
	rt->objects[idx].type = SPHERE;
	printf (BLUE "parsing sphere! [%s] idx [%i]\n", line, idx);
	// line = set_pos(line, &rt->objects[idx]);
	// rt->objects[idx].colour = ft_calloc(1, sizeof(t_vec));
	rt->objects[idx].colour[R] = 42;
	// rt->objects[idx].diameter = ft_atod(line);
	// while (*line && (ft_isdigit(*line) || *line == '.'))
	// 	line++;
	// while (*line && ft_isspace(*line))
	// 	line++;
	// line = set_rgb(line, &rt->objects[idx]);
	printf ("pos?: [%f][%f][%f]\n", rt->objects[idx].pos[X], rt->objects[idx].pos[Y], rt->objects[idx].pos[Z]);
	printf ("diameter: %f\n", rt->objects[idx].diameter);
	printf ("colour?: [%f][%f][%f]\n", rt->objects[idx].colour[R], rt->objects[idx].colour[G], rt->objects[idx].colour[B]);
	printf (END "\n");
	//todo: check for additional input that isnt needed?
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

bool	parse_camera(char *line, t_raytracer *rt, int idx)
{
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

	rt->camera.pos = rt->objects[idx].pos;
	rt->camera.direction = rt->objects[idx].angle;
	rt->camera.fov = rt->objects[idx].fov;

	rt->camera.view_height = 2.0;
	rt->camera.view_width = 2.0;
	rt->camera.focal_length = 1.0;

	rt->camera.horizontal = (t_vec){rt->camera.view_width, 0, 0};
	rt->camera.vertical = (t_vec){0, rt->camera.view_height, 0};
	rt->camera.low_left_corner = rt->camera.pos - (rt->camera.horizontal / 2) - (rt->camera.vertical/2) - (t_vec){0,0,rt->camera.focal_length};
	//todo: check for additional input that isnt needed?	
	return (true);
}
