/* ************************************************************************** */
/*   Space_Simulator — exit_program.c                                         */
/* ************************************************************************** */

#include "includes/exit.h"
#include "../includes/debug.h"

void	exit_prog(t_data *d, int exit_code, const char *error_message)
{
	if (error_message)
		print_error(error_message);

	if (d->ctx)
		SDL_GL_DeleteContext(d->ctx);

	if (d->win)
		SDL_DestroyWindow(d->win);

	SDL_Quit();


	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}
