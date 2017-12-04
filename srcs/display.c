/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:32:18 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/04 12:58:42 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint		create_shader()
{
	const char* vertex_shader =
	"#version 400\n"
	"layout(location = 0) in vec3 vertex_position;"
	"layout(location = 1) in vec3 vertex_colour;"
	"out vec3 colour;"
	"void main() {"
	"  colour = vertex_colour;"
	"  gl_Position = vec4(vertex_position, 1.0);"
	"}";
	const char* fragment_shader =
	"#version 400\n"
	"in vec3 colour;"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(1.0, 1.0, 0.0, 1.0);"
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
	return(shader_programme);
}

void		draw_face(t_object obj, int size)
{
	int			face_i;
	int			points_i;
	int			list_i;
	GLfloat		*points;
	t_vector	rot;

	rot.x = 0;
	rot.y = 0;
	rot.z = 0;
	face_i = 0;
	list_i = 0;
	points_i = 0;

	float colours[] = {
		0.5f, 0.0f,  0.0f,
		0.0f, 0.5f,  0.0f,
		0.0f, 0.0f,  0.5f
	};

	if (!(points = (float*)malloc(size * 3 * sizeof(GLfloat))))
		return;
	while (list_i < obj.face_count)
	{
		while(face_i < 3)
		{
			rotation(obj.vertices[obj.faces[list_i][face_i] - 1], rot);
			points[points_i++] = obj.vertices[obj.faces[list_i][face_i] - 1][0] / 3;
			points[points_i++] = obj.vertices[obj.faces[list_i][face_i] - 1][1] / 3;
			points[points_i++] = obj.vertices[obj.faces[list_i][face_i++] - 1][2] / 3;
		}
		face_i = 0;
		list_i++;
	}
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);

	GLuint colours_vbo = 0;
	glGenBuffers(1, &colours_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colours, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, size);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &colours_vbo);
	free(points);
}

void		display(t_object object)
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	GLuint shader_programme = create_shader();
	glUseProgram(shader_programme);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_face(object, object.face_count * 3);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shader_programme);
}