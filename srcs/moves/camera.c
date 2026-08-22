/* ************************************************************************** */
/*   Space_Simulator — camera.c                                               */
/* ************************************************************************** */

#include "../data.h"
#include "../simulation.h"

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

static void	rotate_movement(t_data *d, t_camera *cam, double speed_init)
{
	double	speed;

	d->cam_target = -1;
	speed = speed_init;
	if (d->input.up == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->ver_n, sin(speed)));
	else if (d->input.down == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->ver_n, -sin(speed)));
	if (d->input.left == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->hor_n, -sin(speed)));
	else if (d->input.right == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->hor_n, sin(speed)));
	vec_normalize(&(cam->dir));
}

static void	linear_movement(t_data *d, t_camera *cam, double speed)
{
	d->cam_target = -1;
	if (d->input.w == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, speed));
	if (d->input.s == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, -speed));
	if (d->input.a == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, -speed));
	if (d->input.d == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, speed));
	if (d->input.ctrl == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, -speed));
	if (d->input.space == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, speed));
}

static bool	update_cam_free(t_data *d, double speed, double speed_rot)
{
	if (d->input.a || d->input.w || d->input.d || d->input.s
		|| d->input.ctrl || d->input.space)
		linear_movement(d, &d->sim.cam, speed);
	else if (d->input.left || d->input.right
		|| d->input.down || d->input.up)
		rotate_movement(d, &d->sim.cam, speed_rot);
	// else if (d->input.i || d->input.o)
	// 	update_fov(d, &d->sim.cam, speed);
	// else if (d->input.r == true)
	// 	reparse(d);
	// else if (d->input.n == true)
	// 	snap_cam_to_planet(d, +1);
	// else if (d->input.p == true)
	// 	snap_cam_to_planet(d, -1);
	else
		return (false);
	calcul_viewport(&d->sim.cam, (double)d->win_w / (double)d->win_h);
	return (true);
}

void	update_cam(t_data *d, double speed, double speed_rot)
{
	// if (d->cam_target >= 0)
	// 	return (update_cam_orbit(d, speed));
	update_cam_free(d, speed, speed_rot);
}
