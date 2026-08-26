/* ************************************************************************** */
/*   Space_Simulator — format_unique.c                                        */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../exit/exit.h"

// Modifier car pas vraiment de parsing encore.
// Camera codee en dur : origine (0,0,-20), direction +z, fov 70.
void	add_cam(t_data *d, char **line_split)
{
	static bool cam = false;

	if (cam == true)
		exit_prog(d, ERROR_FILE_CAM, ERROR_FILE_CAM_MSG);
	cam = true;

	if (check_idx_string_tab(line_split, 3))
	{
		if (!double_valid(line_split[3]))
			exit_prog(d, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
		d->sim.cam.origin = get_vec(d, line_split[1]);
		d->sim.cam.dir = get_vec(d, line_split[2]);
		if (d->sim.cam.dir.x == 0.0 && d->sim.cam.dir.y == 0.0
			&& d->sim.cam.dir.z == 0.0)
			exit_prog(d, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
		vec_normalize(&d->sim.cam.dir);
		d->sim.cam.fov = ft_atod(line_split[3]);
	}
	else
		exit_prog(d, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
	if (d->sim.cam.fov <= 0.0 || d->sim.cam.fov >= 180.0)
		exit_prog(d, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
}

void	add_al(t_data *d, char **line_split)
{
	static bool al = false;

	if (al == true)
		exit_prog(d, ERROR_FILE_AL, ERROR_FILE_AL_MSG);
	al = true;
	if (check_idx_string_tab(line_split, 2))
	{
		if (!double_valid(line_split[1]))
			exit_prog(d, ERROR_FILE_AL, ERROR_FILE_AL_ARGS_MSG);
		d->sim.ambient_ratio = ft_atod(line_split[1]);
		d->sim.ambient = get_color(d, line_split[2]);
	}
	else
		exit_prog(d, ERROR_FILE_AL, ERROR_FILE_AL_ARGS_MSG);
	if (d->sim.ambient_ratio < 0.0 || d->sim.ambient_ratio > 1.0)
		exit_prog(d, ERROR_FILE_AL, ERROR_FILE_AL_ARGS_MSG);
}
