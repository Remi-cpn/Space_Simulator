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

		// Creation de l'image
		glUseProgram(d.program);
		// Dispatch un peu comme du multi threading
		glDispatchCompute(WIN_W/16, WIN_H/16, 1);
		// Control que la generation de l'image est finit
		glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);

		// Copie l'image calculée par le compute shader vers l'écran
		glBindFramebuffer(GL_READ_FRAMEBUFFER, d.fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, WIN_W, WIN_H, 0, 0, WIN_W, WIN_H, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		// Envoi l'image sur l'ecran
		SDL_GL_SwapWindow(d.win);
	}

	exit_prog(&d, EXIT_SUCCESS, NULL);
	return (0);
}