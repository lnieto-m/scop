/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:15:29 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/11 14:17:34 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		upload_texture(char *texture_data)
{
	GLuint	texture;

	texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 626, 626, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, texture_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLint		create_vbo(int size, int data_size, float *data)
{
	GLuint	id;

	id = 0;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data_size * size * sizeof(float), data,
		GL_STATIC_DRAW);
	return (id);
}

void		bind_vbo(int index, GLuint id, int size)
{
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, NULL);
}

void		pass_uniforms(t_object *obj, GLuint shader_programme)
{
	GLint	rotation_y;
	GLint	projection;
	GLint	view;
	GLint	scale;
	GLint	translation;

	rotation_y = glGetUniformLocation(shader_programme, "rotationy");
	projection = glGetUniformLocation(shader_programme, "projection");
	view = glGetUniformLocation(shader_programme, "view");
	scale = glGetUniformLocation(shader_programme, "scale");
	translation = glGetUniformLocation(shader_programme, "translation");
	glUniformMatrix4fv(rotation_y, 1, GL_FALSE, obj->rotation_matrix);
	glUniformMatrix4fv(projection, 1, GL_FALSE, obj->projection_matrix);
	glUniformMatrix4fv(view, 1, GL_FALSE, obj->view_matrix);
	glUniformMatrix4fv(scale, 1, GL_FALSE, obj->scale_matrix);
	glUniformMatrix4fv(translation, 1, GL_FALSE, obj->translation_matrix);
	glUniform1f(glGetUniformLocation(shader_programme, "transition"),
		obj->transition_value);
}
