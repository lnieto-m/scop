/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:30:29 by lnieto-m          #+#    #+#             */
/*   Updated: 2017/12/11 14:15:01 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static GLchar		*load_shader(char *filename)
{
	int				fd;
	char			*line;
	char			*result;
	int				err;
	char			*tmp;

	fd = open(filename, O_RDONLY);
	result = ft_strdup("");
	while ((err = get_next_line(fd, &line)) > 0)
	{
		if (err == -1)
			return ("#version 400\nvoid main(){}\n");
		tmp = ft_strjoin(result, line);
		free(result);
		free(line);
		result = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	return (result);
}

GLuint				create_shader_program(void)
{
	const GLchar	*vertex_shader;
	const GLchar	*fragment_shader;
	GLuint			vs;
	GLuint			fs;
	GLuint			shader_programme;

	vertex_shader = (const GLchar *)load_shader(VERTEX_SHADER);
	fragment_shader = (const GLchar *)load_shader(FRAGMENT_SHADER);
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &(vertex_shader), NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &(fragment_shader), NULL);
	glCompileShader(fs);
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	free((char *)vertex_shader);
	free((char *)fragment_shader);
	return (shader_programme);
}
