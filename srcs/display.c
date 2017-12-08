/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:32:18 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/08 11:16:55 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint		create_shader()
{
	const char* vertex_shader =
	"#version 400\n"
	"layout(location = 0) in vec3 vertex_position;"
	"layout(location = 1) in vec3 vertex_color;"
	"layout(location = 2) in vec2 vertexUV;"
	"uniform mat4 rotationy;"
	"uniform mat4 projection;"
	"uniform mat4 view;"
	"uniform mat4 scale;"
	"uniform mat4 translation;"
	"uniform float transition;"
	"out vec3 fragmentColor;"
	"out vec2 UV;"
	"out float transition_value;"
	"void main() {"
	"  mat4 transl = mat4("
	"	 vec4(1.0, 0.0, 0.0, 0.0),"
	"	 vec4(0.0, 1.0, 0.0, 0.0),"
	"	 vec4(0.0, 0.0, 1.0, 0.0),"
	"	 vec4(0.3, -0.5, -3.0, 1.0)"
	"  );"
	"  fragmentColor = vertex_color;"
	"  mat4 model = transl * rotationy * scale;"
	"  mat4 MVP = projection * model;"
	"  gl_Position = MVP * vec4(vertex_position, 1.0);"
	"  UV = vertexUV;"
	"  transition_value = transition;"
	"}";
	const char* fragment_shader =
	"#version 400\n"
	"in vec3 fragmentColor;"
	"in vec2 UV;"
	"in float transition_value;"
	"uniform sampler2D myTextureSampler;"
	"out vec4 frag_colour;"
	"void main() {"
	"  vec4 text = vec4(texture(myTextureSampler, UV).rgb, 1.0);"
	"  vec4 colour = vec4(fragmentColor, 1.0);"
	"  frag_colour = mix(text, colour, transition_value);"
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
	glUseProgram(shader_programme);
	GLint rotation_y = glGetUniformLocation(shader_programme, "rotationy");
	GLint projection = glGetUniformLocation(shader_programme, "projection");
	GLint view = glGetUniformLocation(shader_programme, "view");
	GLint scale = glGetUniformLocation(shader_programme, "scale");
	GLint translation = glGetUniformLocation(shader_programme, "translation");

	glUniformMatrix4fv(rotation_y, 1, GL_FALSE, obj.rotation_matrix);
	glUniformMatrix4fv(projection, 1, GL_FALSE, obj.projection_matrix);
	glUniformMatrix4fv(view, 1, GL_FALSE, obj.view_matrix);
	glUniformMatrix4fv(scale, 1, GL_FALSE, obj.scale_matrix);
	glUniformMatrix4fv(translation, 1, GL_FALSE, obj.translation_matrix);

	glUniform1f(glGetUniformLocation(shader_programme, "transition"), obj.transition_value);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 626, 626, 0, GL_BGRA, GL_UNSIGNED_BYTE, obj.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), obj.points, GL_STATIC_DRAW);

	GLuint vbocolors = 0;
	glGenBuffers(1, &vbocolors);
	glBindBuffer(GL_ARRAY_BUFFER, vbocolors);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), obj.colors, GL_STATIC_DRAW);

	GLuint vbouv = 0;
	glGenBuffers(1, &vbouv);
	glBindBuffer(GL_ARRAY_BUFFER, vbouv);
	glBufferData(GL_ARRAY_BUFFER,  size * 2 * sizeof(GLfloat), obj.uv_map, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbocolors);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vbouv);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, size);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vbocolors);
	glDeleteBuffers(1, &vbouv);
}

void		display(t_object object, GLint shader_programme)
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_face(object, object.face_count * 3, shader_programme);
	glDeleteVertexArrays(1, &vao);
}
