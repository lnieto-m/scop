/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:11:00 by hivian            #+#    #+#             */
/*   Updated: 2017/11/25 14:19:37 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>

int		BGONETHOT_display(void)
{
	printf("blblblblb\n");
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	float points[]= {
		0.0f,  0.5f,  0.0f,
   		0.5f, -0.5f,  0.0f
		-0.5f, -0.5f,  1.0f
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	const char* vertex_shader =
	"#version 400\n"
	"in vec3 vp;"
	"void main() {"
	"  gl_Position = vec4(vp, 1.0);"
	"}";
	const char* fragment_shader =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(0.5, 0.5, 0.5, 1.0);"
	"}";
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
	return(0);
}

int					main(int ac, char **av)
{
	t_env			e;

	if (ac > 1)
		object_loader(av[1], &e.object);
	if (!(e.mlx = mlx_init()))
	{
		ft_putendl("Env error");
		return (-1);
	}
	e.win = mlx_new_opengl_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "scop");
	mlx_opengl_window_set_context(e.win);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	ft_putstr("Renderer: ");
	ft_putendl((char *)renderer);
	ft_putstr("OpenGL version supported: ");
	ft_putendl((char *)version);
	display(e.object);
	printf("faces: %i, vertices: %i\n", e.object.face_count, e.object.vertices_count);
	mlx_opengl_swap_buffers(e.win);
	mlx_loop(e.mlx);
	return (0);
}
