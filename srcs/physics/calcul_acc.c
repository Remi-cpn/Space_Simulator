/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_acc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/09/17 11:17:16 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "../simulation/simulation.h"
#include "../data.h"

static t_vec	gravity_from(t_physics *dst, t_physics *src)
{
	t_vec	dir;
	t_vec	acc;
	double	dist;

	dir = vec_sub(src->cur_pos, dst->cur_pos);
	dist = vec_norm(dir);
	if (dist < 0.001)
		return ((t_vec){0, 0, 0});
	vec_normalize(&dir);
	acc = vec_mult_scalar(dir, G_CONST * src->mass / (dist * dist));
	return (acc);
}

void	calc_acc_sun(t_simulation *sim, int i)
{
	t_vec	acc;
	int		j;

	if (i >= sim->nb_sun || !sim->suns[i].physics_enabled)
		return ;
	vec_init(&acc, 0, 0, 0);
	j = -1;
	while (++j < sim->nb_sun)
		if (j != i && sim->suns[j].physics_enabled)
			acc = vec_add(acc, gravity_from(
						&sim->suns[i].param,
						&sim->suns[j].param));
	j = -1;
	while (++j < sim->nb_obj)
		if (sim->objs[j].physics_enabled)
			acc = vec_add(acc, gravity_from(
						&sim->suns[i].param,
						&sim->objs[j].shape.sphere.param));
	sim->suns[i].param.acc = acc;
}

// PHYS_ACC dimensionne les jobs sur max(nb_obj, nb_sun) : un index qui
// deborde nb_obj est normal si la scene a plus de soleils que d'objets.
void	calc_acc_obj(t_simulation *sim, int i)
{
	int		j;
	t_vec	acc;

	if (i >= sim->nb_obj || !sim->objs[i].physics_enabled)
		return ;
	j = -1;
	ft_memset(&acc, 0, sizeof(t_vec));
	while (++j < sim->nb_obj)
	{
		if (j == i || !sim->objs[j].physics_enabled)
			continue ;
		acc = vec_add(acc, gravity_from(
					&sim->objs[i].shape.sphere.param,
					&sim->objs[j].shape.sphere.param));
	}
	j = -1;
	while (++j < sim->nb_sun)
	{
		acc = vec_add(acc, gravity_from(
					&sim->objs[i].shape.sphere.param,
					&sim->suns[j].param));
	}
	vec_init(&sim->objs[i].shape.sphere.param.acc, acc.x, acc.y, acc.z);
}
