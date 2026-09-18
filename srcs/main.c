/* ************************************************************************** */
/*   Space_Simulator — main.c                                                 */
/*   Entry point : parses argv, builds the scene, runs the render loop.       */
/* ************************************************************************** */

#include "data.h"
#include "exit/exit.h"
#include "events/events.h"
#include "parsing/parsing.h"
#include "debug/debug.h"
#include "shaders/shader.h"

/*	Main render loop : events, GPU rendering, camera movement,
	window swap.	*/
static void	update(t_data *d)
{
	bool	running;
	running = true;

	while (running)
	{
		running = lisen_poll_event(d);
		params_gl(d);
		update_cam(d, 0.6 * d->wheel_coef, 0.1);
		// Sends the image to the screen
		SDL_GL_SwapWindow(d->win);

		for (int i = 0; i < d->speed_sim; ++i)
			recalcul_physics(d, &d->sim);
		if (d->speed_sim > 0)
		{
			upload_sphere_buffer(d);
			upload_ring_buffer(d);
		}
	}

}

/*	Initializes the program, builds the scene, then runs the render
	loop until closing.	*/
int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2)
	{
		ft_print_error((ac < 2) ? "Need file name." : "Too many args.");
		return (1);
	}

	d = init_program();

	parsing(&d, av[1]);
	init_threads(&d);

	update(&d);

	exit_prog(&d, EXIT_SUCCESS, NULL);
	return (0);
}
