/* ************************************************************************** */
/*   Space_Simulator — parcing.c                                              */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(t_data *d, char *file_name)
{
	(void)file_name;

	add_cam(&(d->sim), NULL);
	// Initialisation de la structure simulation
	init_sim(d);
	d->sim.sky.tex = load_texture(d, "assets/textures/skybox.jpg");
}