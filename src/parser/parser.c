/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 19:14:07 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/16 22:08:18 by root          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//simple
void	alloc_objects(char *av, t_raytracer *rt)
{
	int		obj_count;
	char	*line;
	int		fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		rt_error("Failed to open map");
	obj_count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp("", line, 1) != 0)
			obj_count++;
		if (line)
			free (line);
	}
	if (line)
		free (line);
	rt->objects = ft_calloc(obj_count + 1, sizeof(t_obj));
	if (!rt->objects)
		rt_error("Failed to allocate for objects");
	printf ("obj count?: %i\n", obj_count);
}

//todo: Add an open to write parsing into a .txt?
bool	open_scene(char **av, t_raytracer *rt)
{
	int		fd;
	char	*line;

	alloc_objects(av[1], rt);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		rt_error("Failed to open map");
	printf ("hey!\n");

	while (get_next_line(fd, &line) > 0)
	{
		// printf ("?: %s\n", line);
		if (ft_strncmp("sp ", line, 3) == 0)
			parse_sphere(line + 3, rt, rt->obj_idx++);
		// else if (ft_strncmp("pl ", line, 3) == 0)
		// 	parse_plane(line + 3, rt, rt->obj_idx++);
		// else if (ft_strncmp("cy ", line, 3) == 0)
		// 	parse_cylinder(line + 3, rt, rt->obj_idx++);
		// else if (ft_strncmp("C ", line, 2) == 0)
		// 	parse_camera(line + 2, rt, rt->obj_idx++);
		// else if (ft_strncmp("A ", line, 2) == 0)
		// 	parse_sphere(line + 2);
		// else if (ft_strncmp("L ", line, 2) == 0)
		// 	parse_sphere(line + 2);
		if (line)
			free (line);
	}
	if (line)
		free (line);
	return (true);
}
