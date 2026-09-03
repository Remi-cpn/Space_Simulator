/* ************************************************************************** */
/*   Space_Simulator — parsing_texture.c                                      */
/*   Wires a texture (and optional bump map) parsed from the .ss file to      */
/*   the GL texture cache (init_texture.c).                                   */
/* ************************************************************************** */

#include "parsing.h"
#include "../exit/exit.h"
#include <stdio.h>

void	pars_texture_map(t_data *d, t_texture *t, char *texture_file,
	char *bump_file)
{
	t->type = TEX_IMG;
	t->id = load_texture(d, texture_file);
	if (!bump_file)
		return ;
	t->bump_m = true;
	t->bump_map_id = load_texture(d, bump_file);
}
