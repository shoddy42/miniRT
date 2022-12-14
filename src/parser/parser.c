/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 19:14:07 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/14 19:55:50 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool	open_scene(char **av, t_raytracer *rt)
{
	int fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		rt_error("Failed to open map");
	printf ("hey!\n");
	while (get_next_line(fd, &line) > 0)
	{
		printf ("?: %s\n", line);
		if (ft_strncmp("sp ", line, 3) == 0)
			parse_sphere(line + 3, rt);
		// else if (ft_strncmp("pl ", line, 3) == 0)
		// 	parse_sphere(line + 3);
		// else if (ft_strncmp("cy ", line, 3) == 0)
		// 	parse_sphere(line + 3);
		// else if (ft_strncmp("C ", line, 2) == 0)
		// 	parse_sphere(line + 2);
		// else if (ft_strncmp("A ", line, 2) == 0)
		// 	parse_sphere(line + 2);
		// else if (ft_strncmp("L ", line, 2) == 0)
		// 	parse_sphere(line + 2);
	}
	return (true);
}
