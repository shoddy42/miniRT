/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 14:49:40 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/15 16:23:31 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	*set_pos(char *line, t_obj *obj)
{
	obj->pos[X] = ft_atod(line);
	line = ft_strchr(line, ',') + 1;
	if (!line)
		rt_error("No Y in line!\n");
	obj->pos[Y] = ft_atod(line);
	line = ft_strchr(line, ',') + 1;
	if (!line)
		rt_error("No Z in line!\n");
	obj->pos[Z] = ft_atod(line);
	if (*line == '-' || *line == '+')
		line++;
	while (*line && (ft_isdigit(*line) || *line == '.'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}

char	*set_rgb(char *line, t_obj *obj)
{
	obj->colour[R] = ft_atod(line);
	if (obj->colour[R] > 255 || obj->colour[R] < 0)
		rt_error("R value must be in range of [0 - 255]!\n");
	line = ft_strchr(line, ',') + 1;
	if (!line)
		rt_error("No G in line!\n");
	obj->colour[G] = ft_atod(line);
	line = ft_strchr(line, ',') + 1;
	if (obj->colour[G] > 255 || obj->colour[G] < 0)
		rt_error("G value must be in range of [0 - 255]!\n");
	if (!line)
		rt_error("No B in line!\n");
	obj->colour[B] = ft_atod(line);
	if (obj->colour[B] > 255 || obj->colour[B] < 0)
		rt_error("B value must be in range of [0 - 255]!\n");
	if (*line == '-' || *line == '+')
		line++;
	while (*line && (ft_isdigit(*line) || *line == '.'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}

char	*set_orientation(char *line, t_obj *obj)
{
	obj->angle[X] = ft_atod(line);
	if (obj->angle[X] > 1 || obj->angle[X] < -1)
		rt_error("X value must be in range of [-1 - 1]!\n");
	line = ft_strchr(line, ',') + 1;
	if (!line)
		rt_error("No Y in line!\n");
	obj->angle[Y] = ft_atod(line);
	line = ft_strchr(line, ',') + 1;
	if (obj->angle[Y] > 1 || obj->angle[Y] < 0)
		rt_error("Y value must be in range of [-1 - 1]!\n");
	if (!line)
		rt_error("No Z in line!\n");
	obj->angle[Z] = ft_atod(line);
	if (obj->angle[Z] > 1 || obj->angle[Z] < -1)
		rt_error("Z value must be in range of [-1 - 1]!\n");
	if (*line == '-' || *line == '+')
		line++;
	while (*line && (ft_isdigit(*line) || *line == '.'))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}
