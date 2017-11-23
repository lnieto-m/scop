/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 10:44:13 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/11/23 11:52:31 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "mlx_macros.h"
# include "libftprintf.h"
# include <mlx.h>
# include <mlx_opengl.h>
# include <math.h>
# include <stdbool.h>
# include <openGL/gl3.h>

# define WIN_WIDTH		640
# define WIN_HEIGHT		480
# define MAP_WIDTH		24
# define MAP_HEIGHT		24

# define TRUE			1
# define FALSE			0

# define WHITE			"\033[0m"
# define GREEN			"\033[32m"
# define BLUE			"\033[1;34m"
# define CYAN			"\033[36m"
# define RED			"\033[31m"
# define GREY			"\033[1;30m"
# define YELLOW			"\033[33m"

typedef struct s_color	t_color;
typedef struct s_pos	t_pos;
typedef struct s_env	t_env;
typedef struct s_objct	t_object;
typedef int				(*t_tab)(int, int, int, t_env *);

struct			s_color
{
	int			x;
	int			y;
	int			red;
	int			green;
	int			blue;
};

struct			s_object
{
	char		*name;
	float		vertices[4];
	float		**faces;
	int			shading;
};

struct			s_pos
{
	double		zoom;
	double		x;
	double		y;
	double		move_x;
	double		move_y;
};

struct			s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	int			handle_red;
	int			handle_green;
	int			handle_blue;
	int			max_iter;
	int			flag;
	int			stop_time;
	t_pos		pos;
	t_tab		tab[5];
	t_color		color;
	t_object	object;
};

#endif
