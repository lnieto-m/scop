/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 10:44:13 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/07 18:45:31 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "mlx_macros.h"
# include "libftprintf.h"
# include <mlx.h>
# include <mlx_opengl.h>
# include <stdio.h>
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
	float		*points;
	int			**faces;
	int			shading;
	double		rotation_y;
	char		*texture;
	float 		*uv_map;
	int 		transition_state;
	float		transition_value;
	GLfloat		*projection_matrix;
	GLfloat		*translation_matrix;
	GLfloat		*scale_matrix;
	GLfloat		*rotation_matrix;
	GLfloat		*view_matrix;
	t_vector	position;
};

struct			s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	t_object	object;
	GLuint		shader_programme;
};

void			display(t_object object, GLint shader_programme);
GLuint			create_shader();
void			init_object(t_object *obj, char *filename);
int				object_loader(char *file_name, t_object *object);
GLfloat			*uv_map(int size);

/*
** Matrices
*/

GLfloat 		*create_matrix(int size);
void			rotation_y_matrix(GLfloat *matrix, float angle);
void			projection_matrix(GLfloat *matrix, float fov, float aspect);
void			translation_matrix(GLfloat *matrix, float x, float y, float z);
void			scale_matrix(GLfloat *matrix, float x, float y, float z);

void			load_texture(t_env *e);
float			*generate_colors(int obj_size);
int				key_p(int keycode, t_env *e);

#endif
