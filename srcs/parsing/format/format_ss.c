/* ************************************************************************** */
/*   Space_Simulator — format_ss.c                                        */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../exit/exit.h"
#include <stdio.h>

// "NULL" litteral dans le fichier -> pas de nom (NULL), sinon copie la
// chaine. Utilise par tous les add_* pour rester coherent avec la
// convention deja en place pour les textures optionnelles.
static char	*get_name(char *s)
{
	if (!ft_strncmp(s, "NULL", 5))
		return (NULL);
	return (ft_strdup(s, 0));
}

void	add_light(t_data *d, char **line_split)
{
	static int	i = 0;

	if (check_idx_string_tab(line_split, 4))
	{
		if (!double_valid(line_split[3]))
			exit_prog(d, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_ARGS_MSG);
		d->sim.lights[i].name = get_name(line_split[1]);
		d->sim.lights[i].position = get_vec(d, line_split[2]);
		d->sim.lights[i].intensity = ft_atod(line_split[3]);
		d->sim.lights[i].color = get_color(d, line_split[4]);
	}
	else
		exit_prog(d, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_ARGS_MSG);
	if (d->sim.lights[i].intensity < 0.0 || d->sim.lights[i].intensity > 1.0)
		exit_prog(d, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_ARGS_MSG);
	++i;
	if (i == d->sim.nb_light)
		i = 0;
}

// <Identifiant> <Nom> <Position> <Masse> — trou noir traite a part,
// hors de l'union t_object (voir "Dette technique" du README).
void	add_bh(t_data *d, t_blackhole *bh, char **l_split)
{
	if (check_idx_string_tab(l_split, 3))
	{
		if (!double_valid(l_split[3]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_BH_ARGS_MSG);
		bh->name = get_name(l_split[1]);
		bh->pos = get_vec(d, l_split[2]);
		bh->mass = ft_atod(l_split[3]);
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_BH_ARGS_MSG);
	if (bh->mass <= 0.0)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_BH_ARGS_MSG);
}

// <Identifiant> <Nom> <Position> <Rayon> <Couleur> <RotationSpeed>
// <Masse> <Velocity> <Texture> <Bumpmap> — masse/velocity pas encore
// branches (physique desactivee), reserves pour plus tard.
void	add_sp_solar(t_data *d, t_object *o, char **l_split)
{
	if (check_idx_string_tab(l_split, 9))
	{
		if (!double_valid(l_split[3]) || !double_valid(l_split[5]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
		o->type = OBJ_SPHERE;
		o->physics_enabled = false;
		o->name = get_name(l_split[1]);
		o->shape.sphere.center = get_vec(d, l_split[2]);
		o->shape.sphere.radius = ft_atod(l_split[3]) / 2.0;
		o->color = get_color(d, l_split[4]);
		o->shape.sphere.rotation = 0.0;
		o->shape.sphere.rotation_speed = ft_atod(l_split[5]);
		if (ft_strncmp(l_split[8], "NULL", 5))
		{
			if (ft_strncmp(l_split[9], "NULL", 5))
				pars_texture_map(d, &(o->texture), l_split[8], l_split[9]);
			else
				pars_texture_map(d, &(o->texture), l_split[8], NULL);
		}
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

// <Identifiant> <Nom> <Normale> <RayonInterieur> <RayonExterieur>
// <Couleur> <Texture> <Bumpmap>
void	add_ri(t_data *d, t_object *o, char **l_split, int idx)
{
	if (check_idx_string_tab(l_split, 7))
	{
		if (!double_valid(l_split[3]) || !double_valid(l_split[4]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		o->type = OBJ_RING;
		o->physics_enabled = false;
		if (idx == 0 || d->sim.objs[idx - 1].type != OBJ_SPHERE)
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		o->name = get_name(l_split[1]);
		o->shape.ring.center = &d->sim.objs[idx - 1].shape.sphere.center;
		o->shape.ring.normal = get_vec(d, l_split[2]);
		if (vec_norm(o->shape.ring.normal) < 0.0001)
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		vec_normalize(&o->shape.ring.normal);
		o->shape.ring.inner_rad = ft_atod(l_split[3]);
		o->shape.ring.outer_rad = ft_atod(l_split[4]);
		o->color = get_color(d, l_split[5]);
		if (ft_strncmp(l_split[6], "NULL", 5))
		{
			if (ft_strncmp(l_split[7], "NULL", 5))
				pars_texture_map(d, &(o->texture), l_split[6], l_split[7]);
			else
				pars_texture_map(d, &(o->texture), l_split[6], NULL);
		}
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
	if (o->shape.ring.inner_rad < 0.0
		|| o->shape.ring.outer_rad <= o->shape.ring.inner_rad
		|| o->shape.ring.center == NULL)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
}

// <Identifiant> <Nom> <Position> <Rayon> <Couleur> <Intensite> <Masse>
// <Velocity> <Texture> <Bumpmap> — masse/velocity pas encore branches.
void	add_so(t_data *d, t_sun *s, char **l)
{
	if (check_idx_string_tab(l, 9))
	{
		if (!double_valid(l[3]) || !double_valid(l[5]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
		s->name = get_name(l[1]);
		s->radius = ft_atod(l[3]) / 2.0;
		s->color = get_color(d, l[4]);
		s->intensity = ft_atod(l[5]);
		if (ft_strncmp(l[8], "NULL", 5))
		{
			if (ft_strncmp(l[9], "NULL", 5))
				pars_texture_map(d, &(s->texture), l[8], l[9]);
			else
				pars_texture_map(d, &(s->texture), l[8], NULL);
		}
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
	if (s->radius <= 0.0 || s->intensity < 0)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
}
