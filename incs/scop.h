/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 10:44:13 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/06 15:03:25 by lnieto-m         ###   ########.fr       */
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
# include <time.h>
# include <fcntl.h>
# include <openGL/gl3.h>

# define WIN_WIDTH		720
# define WIN_HEIGHT		720
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

typedef struct s_env	t_env;
typedef struct s_vector t_vector;
typedef struct s_object	t_object;
typedef int				(*t_tab)(int, int, int, t_env *);

struct			s_vector
{
	float		x;
	float		y;
	float		z;
};

struct			s_object
{
	int			face_count;
	int			vertices_count;
	char		*name;
	float		**vertices;
	float		*colors;
	int			**faces;
	int			shading;
	double		rotation_y;
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
	t_object	object;
};

int				object_loader(char *file_name, t_object *object);
void			display(t_object object);
GLfloat			*rotation_y_matrix(float angle);
GLfloat			*projection_matrix(float fov, float near, float far, float aspect);
float			*generate_colors(int obj_size);
int				key_p(int keycode, t_env *e);

#endif
