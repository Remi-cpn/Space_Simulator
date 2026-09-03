/* ************************************************************************** */
/*   Space_Simulator — shader.c                                               */
/*   Compiles/links the compute shader, sends the per-frame uniforms,         */
/*   dispatches and blits the result to the screen.                           */
/* ************************************************************************** */

#include "shader.h"
#include "../exit/exit.h"
#include <stdio.h>

void	init_object_buffers(t_data *d)
{
	glGenBuffers(1, &d->sphere_ssbo);
	glGenBuffers(1, &d->ring_ssbo);
	glGenBuffers(1, &d->light_ssbo);
	glGenBuffers(1, &d->blackhole_ssbo);
}

/*	Fixes obj_textures[i] -> unit i once and for all (static mapping).
	Textures are bound to these units later, on each (re)load.	*/
void	init_obj_texture_units(t_data *d)
{
	char	name[24];
	int		i;

	glUseProgram(d->program);
	i = 0;
	while (i < OBJ_TEXTURES_MAX)
	{
		snprintf(name, sizeof(name), "obj_textures[%d]", i);
		glUniform1i(glGetUniformLocation(d->program, name), i);
		i++;
	}
}

/*	Sends the current frame's uniforms to the shader and dispatches
	the compute shader, then blits the result to the screen.	*/
void	params_gl(t_data *d)
{
		// Image creation
		glUseProgram(d->program);

		// Ensures what's needed every frame is set
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, d->sim.sky.tex);

		// Sets shader.comp uniforms (obj_textures[0] -> skybox, fixed once
		// and for all by init_obj_texture_units)
		glUniform3f(glGetUniformLocation(d->program, "cam_origin"), d->sim.cam.origin.x, d->sim.cam.origin.y, d->sim.cam.origin.z);
		glUniform3f(glGetUniformLocation(d->program, "cam_corner"), d->sim.cam.corner.x, d->sim.cam.corner.y, d->sim.cam.corner.z);
		glUniform3f(glGetUniformLocation(d->program, "cam_hor"),    d->sim.cam.hor.x,    d->sim.cam.hor.y,    d->sim.cam.hor.z);
		glUniform3f(glGetUniformLocation(d->program, "cam_ver"),    d->sim.cam.ver.x,    d->sim.cam.ver.y,    d->sim.cam.ver.z);
		glUniform1i(glGetUniformLocation(d->program, "steps"), d->steps);
		glUniform1f(glGetUniformLocation(d->program, "step_size"), d->step_size);
		glUniform1i(glGetUniformLocation(d->program, "nbr_ray"), d->nbr_ray);
		glUniform1f(glGetUniformLocation(d->program, "exposure"), d->exposure);
		glUniform1f(glGetUniformLocation(d->program, "gamma"), d->gamma);
		glUniform1i(glGetUniformLocation(d->program, "nbr_light"), d->sim.nb_light);
		glUniform1f(glGetUniformLocation(d->program, "shadow_dist"), d->sim.shadow_dist);
		glUniform3f(glGetUniformLocation(d->program, "ambient_color"), d->sim.ambient.r / 255.0f, d->sim.ambient.g / 255.0f, d->sim.ambient.b / 255.0f);
		glUniform1f(glGetUniformLocation(d->program, "ambient_ratio"), d->sim.ambient_ratio);


		// Dispatch, a bit like multithreading
		glDispatchCompute(d->win_w/16, d->win_h/16, 1);
		// Ensures the image generation is finished
		glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);

		// Copies the image computed by the compute shader to the screen
		glBindFramebuffer(GL_READ_FRAMEBUFFER, d->fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, d->win_w, d->win_h, 0, 0, d->win_w, d->win_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

/*	Reads an entire shader file into memory (open/fstat/read), without
	fopen/fread : the exact size is known via fstat before reading.	*/
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

/*	Compiles the GLSL source into a compute shader and checks every
	step : compilation, then linking of the returned program.	*/
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
