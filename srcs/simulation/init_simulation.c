/* ************************************************************************** */
/*   Space_Simulator — init_simulation.c                                      */
/*   Builds the camera's viewport from its dir/fov and the window's           */
/*   resolution.                                                              */
/* ************************************************************************** */

#include "simulation.h"
#include "../parsing/parsing.h"

/*	Builds the camera's orthonormal basis (hor_n/ver_n) and the
	viewport corner, from dir/fov.	*/
void	calcul_viewport(t_camera *cam, double ratio)
{
	double				fov_rad;
	static const t_vec	up = {.x = 0, .y = 1, .z = 0};
	static const t_vec	depth = {.x = 0, .y = 0, .z = 1};

	cam->focal = 1.0;
	if (vec_square(cam->hor_n) < 0.0001)
	{
		cam->hor_n = vec_vectoriel(cam->dir, up);
		if (vec_square(cam->hor_n) < 0.0001)
			cam->hor_n = vec_vectoriel(cam->dir, depth);
		vec_normalize(&cam->hor_n);
	}
	cam->ver_n = vec_vectoriel(cam->hor_n, cam->dir);
	vec_normalize(&cam->ver_n);
	cam->hor_n = vec_vectoriel(cam->dir, cam->ver_n);
	vec_normalize(&cam->hor_n);
	fov_rad = 2 * tan(cam->fov * PI / 360.0);
	cam->hor = vec_mult_scalar(cam->hor_n, ratio * fov_rad);
	cam->ver = vec_mult_scalar(cam->ver_n, fov_rad);
	cam->corner = vec_sub(cam->origin, vec_mult_scalar(cam->hor, 0.5));
	cam->corner = vec_sub(cam->corner, vec_mult_scalar(cam->ver, 0.5));
	cam->corner = vec_add(cam->corner, vec_mult_scalar(cam->dir, cam->focal));
}

/*	Computes the camera's initial viewport from the window's
	resolution.	*/
void	init_sim(t_data *d)
{
	calcul_viewport(&(d->sim.cam), (double)d->win_w / (double)d->win_h);
	d->sim.shadow_dist = SHADOW_DIST;
}
