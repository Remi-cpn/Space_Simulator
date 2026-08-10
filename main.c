/* ************************************************************************** */
/*   Space_Simulator — main.c                                                 */
/* ************************************************************************** */

#include "includes/data.h"
#include "includes/exit.h"
#include "includes/events.h"

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
		running = lisen_poll_event(&d);

		// Creation de l'image
		glUseProgram(d.program);
		// Dispatch un peu comme du multi threading
		glDispatchCompute(d.win_w/16, d.win_h/16, 1);
		// Control que la generation de l'image est finit
		glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);

		// Copie l'image calculée par le compute shader pour l'écran
		glBindFramebuffer(GL_READ_FRAMEBUFFER, d.fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, d.win_w, d.win_h, 0, 0, d.win_w, d.win_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		// Envoi l'image sur l'ecran
		SDL_GL_SwapWindow(d.win);
	}

	exit_prog(&d, EXIT_SUCCESS, NULL);
	return (0);
}