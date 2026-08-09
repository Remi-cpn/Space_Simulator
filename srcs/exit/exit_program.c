/* ************************************************************************** */
/*   Space_Simulator — exit_program.c                                         */
/* ************************************************************************** */

#include "includes/exit.h"

static void	print_error(const char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
}

void	exit_prog(t_data *d, int exit_code, const char *error_message)
{
	if (error_message)
		print_error(error_message);
	if (exit_code < 0)
		exit (EXIT_ERROR);

	if (d->win)
		SDL_DestroyWindow(d->win);

	SDL_Quit();

	exit(exit_code);
}
