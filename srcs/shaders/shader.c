/* ************************************************************************** */
/*   Space_Simulator — shader.c                                               */
/* ************************************************************************** */

#include "shader.h"
#include "../exit/exit.h"

void	init_object_buffers(t_data *d)
{
	glGenBuffers(1, &d->sphere_ssbo);
	glGenBuffers(1, &d->ring_ssbo);
	glGenBuffers(1, &d->sun_ssbo);
}

// Envoie les uniforms de la frame courante au shader et dispatch le
// compute shader, puis blit le resultat a l'ecran.
void	params_gl(t_data *d)
{
		// Creation de l'image
		glUseProgram(d->program);

		// Blinde ce qui est necessaire a chaque fram
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, d->sim.sky.tex);

		// Set uniform de shader.comp
		glUniform1i(glGetUniformLocation(d->program, "skybox"), 0);
		glUniform3f(glGetUniformLocation(d->program, "cam_origin"), d->sim.cam.origin.x, d->sim.cam.origin.y, d->sim.cam.origin.z);
		glUniform3f(glGetUniformLocation(d->program, "cam_corner"), d->sim.cam.corner.x, d->sim.cam.corner.y, d->sim.cam.corner.z);
		glUniform3f(glGetUniformLocation(d->program, "cam_hor"),    d->sim.cam.hor.x,    d->sim.cam.hor.y,    d->sim.cam.hor.z);
		glUniform3f(glGetUniformLocation(d->program, "cam_ver"),    d->sim.cam.ver.x,    d->sim.cam.ver.y,    d->sim.cam.ver.z);
		glUniform1f(glGetUniformLocation(d->program, "bh_mass"), d->sim.blackholes[0].mass);
		glUniform3f(glGetUniformLocation(d->program, "bh_pos"), d->sim.blackholes[0].pos.x, d->sim.blackholes[0].pos.y, d->sim.blackholes[0].pos.z);
		glUniform1i(glGetUniformLocation(d->program, "steps"), 500);
		glUniform1f(glGetUniformLocation(d->program, "step_size"), 1.0f);
		glUniform1i(glGetUniformLocation(d->program, "nbr_ray"), d->nbr_ray);
		glUniform1f(glGetUniformLocation(d->program, "exposure"), d->exposure);
		glUniform1f(glGetUniformLocation(d->program, "gamma"), d->gamma);


		// Dispatch un peu comme du multi threading
		glDispatchCompute(d->win_w/16, d->win_h/16, 1);
		// Control que la generation de l'image est finit
		glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);

		// Copie l'image calculée par le compute shader pour l'écran
		glBindFramebuffer(GL_READ_FRAMEBUFFER, d->fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, d->win_w, d->win_h, 0, 0, d->win_w, d->win_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

// Lit un fichier shader entier en memoire (open/fstat/read), sans passer
// par fopen/fread : on connait la taille exacte via fstat avant de lire.
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

// Compile la source GLSL en compute shader et verifie chaque etape :
// compilation, puis link du program renvoye (pret a etre dispatche).
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
