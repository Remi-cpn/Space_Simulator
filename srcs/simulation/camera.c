/* ************************************************************************** */
/*   Space_Simulator — camera.c                                               */
/*   Free-fly camera controls : movement and rotation from keyboard           */
/*   input.                                                                   */
/* ************************************************************************** */

#include "../data.h"
#include "simulation.h"

/*	Rotates the camera's direction (arrow keys) via incremental
	rotation around its local axes hor_n/ver_n.	*/
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
				vec_mult_scalar(cam->hor_n, sin(speed)));
	else if (d->input.right == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->hor_n, -sin(speed)));
	vec_normalize(&(cam->dir));
}

/*	Moves the camera's origin according to the keys held down
	(WASD + Ctrl/Space for down/up).	*/
static void	linear_movement(t_data *d, t_camera *cam, double speed)
{
	d->cam_target = -1;
	if (d->input.w == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, speed));
	if (d->input.s == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, -speed));
	if (d->input.a == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, speed));
	if (d->input.d == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, -speed));
	if (d->input.ctrl == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, -speed));
	if (d->input.space == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, speed));
}

/*	Applies movement or rotation based on the active keys, then
	recomputes the viewport if something moved.	*/
static bool	update_cam_free(t_data *d, double speed, double speed_rot)
{
	if (d->input.a || d->input.w || d->input.d || d->input.s
		|| d->input.ctrl || d->input.space)
		linear_movement(d, &d->sim.cam, speed);
	else if (d->input.left || d->input.right
		|| d->input.down || d->input.up)
		rotate_movement(d, &d->sim.cam, speed_rot);
	else
		return (false);
	calcul_viewport(&d->sim.cam, (double)d->win_w / (double)d->win_h);
	return (true);
}

/*	Entry point for camera controls (free mode for now, orbit mode
	is disabled/pending for v3).	*/
void	update_cam(t_data *d, double speed, double speed_rot)
{
	update_cam_free(d, speed, speed_rot);
}
