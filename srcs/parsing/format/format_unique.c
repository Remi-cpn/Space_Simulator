/* ************************************************************************** */
/*   Space_Simulator — format_unique.c                                        */
/* ************************************************************************** */

#include "../parsing.h"

// Modifier car pas vraiment de parsing encore
void	add_bh(t_simulation *s, char **line_split)
{
	(void)line_split;
	s->bh.mass = 1;
	s->bh.pos = (t_vec){0, 0, 0};
}

// Modifier car pas vraiment de parsing encore
void	add_cam(t_simulation *s, char **line_split)
{
	(void)line_split;
	// if (p->cam == true)
	// 	exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_MSG);
	// p->cam = true;
	// if (check_idx_string_tab(line_split, 3))
	// {
		// if (!double_valid(line_split[3]))
		// 	exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
		s->cam.origin = (t_vec){0, 0, -20};
		s->cam.dir = (t_vec){0, 0, 1};
		// if (s->cam.dir.x == 0.0 && s->cam.dir.y == 0.0
		// 	&& s->cam.dir.z == 0.0)
		// 	exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
		vec_normalize(&s->cam.dir);
		s->cam.fov = 70;
	// }
	// else
	// 	exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
	// if (s->cam.fov <= 0.0 || s->cam.fov >= 180.0)
	// 	exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
}
