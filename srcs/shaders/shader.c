/* ************************************************************************** */
/*   Space_Simulator — shader.c                                               */
/* ************************************************************************** */

#include "../../includes/shader.h"
#include "../../includes/exit.h"

char	*read_source_compute_shader(t_data *d, char *shader_name)
{
	int			fd;
	int			res;
	int			total_read;
	struct stat	st;
	char		*buffer;
	
	fd = open(shader_name, O_RDONLY);
	if (fd == -1)
		exit_prog(d, ERROR_FILE_SHADER_OPEN, ERROR_FILE_SHADER_OPEN_MSG);
	if (fstat(fd, &st) == -1)
	{
		close(fd);
		exit_prog(d, ERROR_FILE_SHADER_FSTAT, ERROR_FILE_SHADER_FSTAT_MSG);
	}

	buffer = ft_calloc(st.st_size + 1, sizeof(char));
	if (!buffer)
	{
		close(fd);
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	}

	total_read = 0;
	res = 0;
	while (st.st_size > total_read)
	{
		res = read(fd, buffer + total_read, st.st_size - total_read);
		if (res == -1)
		{
			free(buffer);
			close(fd);
			exit_prog(d, ERROR_FILE_SHADER_READ, ERROR_FILE_SHADER_READ_MSG);
		}
		if (res == 0)
			break;
		total_read += res;
	}

	close(fd);
	return (buffer);
}

GLuint	create_compute_shader(t_data *d, char *shader_name)
{
	GLuint			shader_id;
	GLuint			program_id;
	GLint			verif;
	const GLchar	*src;

	src = read_source_compute_shader(d, shader_name);
	if (!src[0])
	{
		free((void *)src);
		exit_prog(d, ERROR_FILE_SHADER_EMPTY, ERROR_FILE_SHADER_EMPTY_MSG);
	}

	shader_id = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(shader_id, 1, &src, NULL);
	free((void *)src);

	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &verif);
	if (verif == GL_FALSE)
		exit_prog(d, ERROR_SHADER_COMPILE, ERROR_SHADER_COMPILE_MSG);

	program_id = glCreateProgram();
	glAttachShader(program_id, shader_id);
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &verif);
	if (verif == GL_FALSE)
		exit_prog(d, ERROR_SHADER_LINK, ERROR_SHADER_LINK_MSG);

	glDeleteShader(shader_id);
	return (program_id);
}
