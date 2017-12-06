/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:32:18 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/06 15:10:29 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint		create_shader()
{
	const char* vertex_shader =
	"#version 400\n"
	"layout(location = 0) in vec3 vertex_position;"
	"layout(location = 1) in vec3 vertex_color;"
	"uniform mat4 rotationy;"
	"uniform mat4 projection;"
	"out vec3 fragmentColor;"
	"void main() {"
	"  mat4 transl = mat4("
	"	 vec4(1.0, 0.0, 0.0, 0.0),"
	"	 vec4(0.0, 1.0, 0.0, 0.0),"
	"	 vec4(0.0, 0.0, 1.0, 0.5),"
	"	 vec4(0.0, 0.0, 0.0, 1.0)"
	"  );"
	"  mat4 scale = mat4("
    "	 vec4(0.2, 0.0, 0.0, 0.0),"
    "	 vec4(0.0, 0.2, 0.0, 0.0),"
    "	 vec4(0.0, 0.0, 0.2, 0.0),"
    "	 vec4(0.0, 0.0, 0.0, 1.0)"
    "  );"
	"  fragmentColor = vertex_color;"
	"  gl_Position = transl * rotationy * scale * vec4(vertex_position, 1.0);"
	"}";
	const char* fragment_shader =
	"#version 400\n"
	"in vec3 fragmentColor;"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(fragmentColor, 1.0);"
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

void		draw_face(t_object obj, int size, GLuint shader_programme)
{
	int			face_i;
	int			points_i;
	int			list_i;
	GLfloat		*points;

	face_i = 0;
	list_i = 0;
	points_i = 0;
	srand(time(NULL));
	if (!(points = (float*)malloc(size * 3 * sizeof(GLfloat))))
		return;
	while (list_i < obj.face_count)
	{
		while(face_i < 3)
		{
			points[points_i++] = obj.vertices[obj.faces[list_i][face_i] - 1][0];
			points[points_i++] = obj.vertices[obj.faces[list_i][face_i] - 1][1];
			points[points_i++] = obj.vertices[obj.faces[list_i][face_i++] - 1][2];
		}
		face_i = 0;
		list_i++;
	}
	glUseProgram(shader_programme);
	GLint rotation_y = glGetUniformLocation(shader_programme, "rotationy");
	GLint projection = glGetUniformLocation(shader_programme, "projection");
	GLfloat *matrix_rotation = rotation_y_matrix(obj.rotation_y);
	GLfloat *matrix_projection = projection_matrix(90.0f, 0.1f, 100.0f, 4.0f / 3.0f);
	glUniformMatrix4fv(rotation_y, 1, GL_FALSE, matrix_rotation);
	glUniformMatrix4fv(projection, 1, GL_FALSE, matrix_projection);
	free(matrix_rotation);
	free(matrix_projection);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);

	GLuint vbocolors = 0;
	glGenBuffers(1, &vbocolors);
	glBindBuffer(GL_ARRAY_BUFFER, vbocolors);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), obj.colors, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbocolors);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, size);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vbocolors);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_face(object, object.face_count * 3, shader_programme);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shader_programme);
}
