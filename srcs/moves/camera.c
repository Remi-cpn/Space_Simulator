/* ************************************************************************** */
/*   Space_Simulator — camera.c                                               */
/* ************************************************************************** */

#include "../data.h"

// void	reparse(t_data *d)
// {
// 	free(d->sim.objects);
// 	d->sim.objects = NULL;
// 	d->sim.nb_obj = 0;
// 	d->sim = parsing(d, d->filename);
// 	d->input.r = false;
// }

// static bool	update_cam_orbit(t_data *d, double speed)
// {
// 	if (d->input.left || d->input.right
// 		|| d->input.up || d->input.down)
// 		orbit_movement(d, ORBIT_SPEED);
// 	else if (d->input.w || d->input.s)
// 		orbit_zoom(d, speed / 50);
// 	else if (d->input.a || d->input.d
// 		|| d->input.ctrl || d->input.space)
// 	{
// 		d->cam_target = -1;
// 		linear_movement(d, &d->sim.camera, speed);
// 	}
// 	else if (d->input.n == true)
// 		snap_cam_to_planet(d, +1);
// 	else if (d->input.p == true)
// 		snap_cam_to_planet(d, -1);
// 	else if (d->input.r == true)
// 		reparse(d);
// 	else
// 		return (false);
// 	follow_cam(d);
// 	return (true);
// }

// bool	update_cam(t_data *d, double speed, double speed_rot)
// {
// 	if (d->cam_target >= 0)
// 		return (update_cam_orbit(d, speed));
// 	return (update_cam_free(d, speed, speed_rot));
// }
