/* ************************************************************************** */
/*   Space_Simulator — parcing.c                                              */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(t_data *d, char *file_name)
{
	(void)file_name;
	(void)d;
	d->sim.sky.tex = load_texture(d, "assets/textures/skybox.jpg");
}