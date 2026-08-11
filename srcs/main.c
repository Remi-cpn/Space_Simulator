/* ************************************************************************** */
/*   Space_Simulator — main.c                                                 */
/* ************************************************************************** */

#include "data.h"
#include "exit/exit.h"
#include "events/events.h"
#include "parsing/parsing.h"

static void	update(t_data *d)
{
	bool	running;
	running = true;

	while (running)
	{
		running = lisen_poll_event(d);

		// Creation de l'image
		glUseProgram(d->program);

		// Blinde ce qui est necessaire a chaque fram
		// Une fois l'archi solude sortir de blocs de code de la boucle
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, d->sim.sky.tex);
		glUniform1i(glGetUniformLocation(d->program, "skybox"), 0);


		// Dispatch un peu comme du multi threading
		glDispatchCompute(d->win_w/16, d->win_h/16, 1);
		// Control que la generation de l'image est finit
		glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);

		// Copie l'image calculée par le compute shader pour l'écran
		glBindFramebuffer(GL_READ_FRAMEBUFFER, d->fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, d->win_w, d->win_h, 0, 0, d->win_w, d->win_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);


		// update_cam(d, 0.6, 0.1);




		// Envoi l'image sur l'ecran
		SDL_GL_SwapWindow(d->win);
	}

}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2 && ac != 3)
		return (1);

	d = init_program();
	parsing(&d, NULL);
	(void)av;

	update(&d);

	exit_prog(&d, EXIT_SUCCESS, NULL);
	return (0);
}
