/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 22:52:56 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/21 01:32:47 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

//Expected to be a normalised value [-1 to 1]
typedef double	t_vec __attribute__ ((vector_size (4 * sizeof(double))));

//Expected to be a normalised value [-1 to 1]
typedef double	t_col __attribute__ ((vector_size (4 * sizeof(double))));

typedef double	t_pnt __attribute__ ((vector_size (4 * sizeof(double))));

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

//Expected to be a normalised value [-1 to 1]
typedef struct s_vector
{
	t_vec	vec;
}	t_vector;

typedef struct s_colour
{
	t_col	col;
}	t_colour;

typedef struct s_point
{
	t_pnt	point;
}	t_point;
#endif