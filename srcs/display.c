/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:32:18 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/11 14:16:11 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		draw_face(t_object *obj, int size, GLuint shader_programme)
{
	glUseProgram(shader_programme);
	pass_uniforms(obj, shader_programme);
	upload_texture(obj->texture);
	obj->vbo = create_vbo(3, obj->face_count * 3, obj->points);
	obj->vbo_colors = create_vbo(3, obj->face_count * 3, obj->colors);
	obj->vbo_uvs = create_vbo(2, obj->face_count * 3, obj->uv_map);
	bind_vbo(0, obj->vbo, 3);
	bind_vbo(1, obj->vbo_colors, 3);
	bind_vbo(2, obj->vbo_uvs, 2);
	glDrawArrays(GL_TRIANGLES, 0, size);
}

void		display(t_object object, GLint shader_programme)
{
	GLuint vao;

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_face(&object, object.face_count * 3, shader_programme);
	glDeleteBuffers(1, &object.vbo);
	glDeleteBuffers(1, &object.vbo_colors);
	glDeleteBuffers(1, &object.vbo_uvs);
	glDeleteVertexArrays(1, &vao);
}
