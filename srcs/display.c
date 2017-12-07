/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:32:18 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/07 15:00:52 by lnieto-m         ###   ########.fr       */
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
	"uniform float transition;"
	"out vec3 fragmentColor;"
	"out vec2 UV;"
	"out float transition_value;"
	"void main() {"
	"  mat4 transl = mat4("
	"	 vec4(1.0, 0.0, 0.0, 0.0),"
	"	 vec4(0.0, 1.0, 0.0, 0.0),"
	"	 vec4(0.0, 0.0, 1.0, 0.0),"
	"	 vec4(0.0, 0.0, 0.0, 1.0)"
	"  );"
	// "  mat4 projection = mat4("
	// "	 vec4(2.41, 0.0, 0.0, 0.0),"
	// "	 vec4(0.0, 2.41, 0.0, 0.0),"
	// "	 vec4(0.0, 0.0, -1.0002002, -0.200200),"
	// "	 vec4(0.0, 0.0, -1.0, 0.0)"
	// "  );"
	"  mat4 scale = mat4("
    "	 vec4(0.3, 0.0, 0.0, 0.0),"
    "	 vec4(0.0, 0.3, 0.0, 0.0),"
    "	 vec4(0.0, 0.0, 0.3, 0.0),"
    "	 vec4(0.0, 0.0, 0.0, 1.0)"
    "  );"
	// "  mat4 view = mat4("
    // "	 vec4(1.0, 0.0, 0.0, 0.0),"
    // "	 vec4(0.0, 1.0, 0.0, 0.0),"
    // "	 vec4(0.0, 0.0, 1.0, 2.0),"
    // "	 vec4(0.0, 0.0, 0.0, 1.0)"
    // "  );"
	"  fragmentColor = vertex_color;"
	"  mat4 model = transl * rotationy * scale;"
	"  mat4 MVP = model;"
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
	GLint view = glGetUniformLocation(shader_programme, "view");
	GLfloat *matrix_rotation = rotation_y_matrix(obj.rotation_y);
	GLfloat *matrix_projection = projection_matrix(45.0f, 0.1f, 100.0f, (float)(WIN_WIDTH / WIN_HEIGHT));
	GLfloat *matrix_view = view_matrix();
	glUniformMatrix4fv(rotation_y, 1, GL_FALSE, matrix_rotation);
	glUniformMatrix4fv(projection, 1, GL_FALSE, matrix_projection);
	glUniformMatrix4fv(view, 1, GL_FALSE, matrix_view);
	free(matrix_rotation);
	free(matrix_projection);
	free(matrix_view);

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
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);

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
	free(points);
}

void		display(t_object object)
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	GLuint shader_programme = create_shader();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_face(object, object.face_count * 3, shader_programme);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shader_programme);
}
