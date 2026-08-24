/* ************************************************************************** */
/*   Space_Simulator — main.c                                                 */
/* ************************************************************************** */

#include "data.h"
#include "exit/exit.h"
#include "events/events.h"
#include "parsing/parsing.h"
#include "debug/debug.h"
#include "shaders/shader.h"

// Boucle de rendu principale : evenements, rendu GPU, deplacement
// camera, swap de la fenetre.
static void	update(t_data *d)
{
	bool	running;
	running = true;

	while (running)
	{
		running = lisen_poll_event(d);
		params_gl(d);
		update_cam(d, 0.6, 0.1);
		// Envoi l'image sur l'ecran
		SDL_GL_SwapWindow(d->win);
	}

}

// Initialise le programme, construit la scene, puis lance la boucle
// de rendu jusqu'a la fermeture.
int	main(int ac, char **av)
{
	t_data	d;

	(void)ac;
	// if (ac != 2 && ac != 3)
	// 	return (1);

	d = init_program();
	parsing(&d, NULL);
	(void)av;

	update(&d);

	exit_prog(&d, EXIT_SUCCESS, NULL);
	return (0);
}
