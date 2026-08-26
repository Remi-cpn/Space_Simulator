/* ************************************************************************** */
/*   Space_Simulator — parsing_texture.c                                      */
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

// void	pars_chessboard(t_parsing *p, t_object *o, char *scale, char *color)
// {
// 	if (double_valid(scale))
// 	{
// 		o->texture.type = TEX_CB;
// 		o->texture.scale = ft_atod(scale);
// 		o->texture.color2 = get_color(p, color);
// 		if (o->texture.scale > 0)
// 			return ;
// 	}
// 	if (o->type == OBJ_SPHERE)
// 		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
// 	if (o->type == OBJ_PLANE)
// 		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_PL_ARGS_MSG);
// 	if (o->type == OBJ_CYLINDER)
// 		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
// 	if (o->type == OBJ_CONE)
// 		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CO_ARGS_MSG);
// }
