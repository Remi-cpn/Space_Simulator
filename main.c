/* ************************************************************************** */
/*   Space_Simulator — main.c                                                 */
/* ************************************************************************** */

#include "includes/data.h"
#include "includes/exit.h"

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2 && ac != 3)
		return (1);

	d = init_program();

	(void)av;

	bool	running;
	running = true;
	while (running)
	{
		SDL_Event ev;

		while (SDL_PollEvent(&ev))
		{
			// Fentre fermee par la croix
			if (ev.type == SDL_QUIT)
				running = false;
			// Fenetre fermee par key
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)
				running = false;
		}

		// Nettoye la fenetre
		glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Envoi l'image sur l'ecran
		SDL_GL_SwapWindow(d.win);
	}

	exit_prog(&d, EXIT_SUCCESS, NULL);
	return (0);
}