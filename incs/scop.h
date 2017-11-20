/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 14:28:44 by hivian            #+#    #+#             */
/*   Updated: 2016/08/17 16:34:44 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "mlx_macros.h"
# include "libft.h"
# include <mlx.h>
# include <mlx_opengl.h>
# include <math.h>
# include <stdbool.h>

# define WIN_WIDTH		700
# define WIN_HEIGHT		500
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
typedef int				(*t_tab)(int, int, int, t_env *);

struct			s_color
{
	int			x;
	int			y;
	int			red;
	int			green;
	int			blue;
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
};

#endif
