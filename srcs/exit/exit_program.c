/* ************************************************************************** */
/*   Space_Simulator — exit_program.c                                         */
/* ************************************************************************** */

#include "exit.h"
#include "../debug/debug.h"

void	exit_prog(t_data *d, int exit_code, const char *error_message)
{
	int	i;

	if (error_message)
		ft_print_error((char *)error_message);
	if (d->ctx)
		SDL_GL_DeleteContext(d->ctx);
	if (d->win)
		SDL_DestroyWindow(d->win);
	if (d->fbo)
		glDeleteFramebuffers(1, &(d->fbo));
	if (d->img)
		glDeleteTextures(1, &(d->img));
	if (d->program)
		glDeleteProgram(d->program);
	if (d->tex)
	{
		i = 0;
		while (i < d->tex_count)
		{
			free(d->tex[i].path);
			glDeleteTextures(1, &(d->tex[i].id));
			i++;
		}
		free(d->tex);
	}
	SDL_Quit();

	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}
