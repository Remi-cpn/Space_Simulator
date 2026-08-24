/* ************************************************************************** */
/*   Space_Simulator — parcing.c                                              */
/* ************************************************************************** */

#include "parsing.h"

// Construit la scene (camera, trou noir codes en dur pour l'instant),
// puis initialise viewport, arbre HUD et skybox.
void	parsing(t_data *d, char *file_name)
{
	(void)file_name;

	add_cam(&(d->sim), NULL);
	add_bh(&(d->sim), NULL);
	// Initialisation de la structure simulation
	init_sim(d);
	init_hud(d);
	d->sim.sky.tex = load_texture(d, "assets/textures/skybox.jpg");
}