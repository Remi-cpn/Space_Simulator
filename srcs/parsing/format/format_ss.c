/* ************************************************************************** */
/*   Space_Simulator — format_ss.c                                            */
/*   Parses the .ss-specific entities (lights, black hole, spheres,           */
/*   rings, suns) into the simulation.                                        */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../exit/exit.h"
#include <stdio.h>

/*	"NULL" literal in the file -> no name (NULL), otherwise copies the
	string. Used by every add_* to stay consistent with the convention
	already in place for optional textures.	*/
static char	*get_name(char *s)
{
	if (!ft_strncmp(s, "NULL", 5))
		return (NULL);
	return (ft_strdup(s, 0));
}

/*	<Identifier> <Name> <Position> <Intensity> <Color>.	*/
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

/*	<Identifier> <Name> <Position> <Mass>.	*/
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

/*	<Identifier> <Name> <Position> <Diameter> <Color> <Shininess>
	<RotationSpeed> <Mass> <Velocity> <Texture> <Bumpmap>.	*/
void	add_sp_solar(t_data *d, t_object *o, char **l_split)
{
	if (check_idx_string_tab(l_split, 10))
	{
		if (!double_valid(l_split[3]) || !double_valid(l_split[5])
			|| !double_valid(l_split[6]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
		o->type = OBJ_SPHERE;
		o->name = get_name(l_split[1]);
		o->shape.sphere.center = get_vec(d, l_split[2]);
		o->shape.sphere.radius = ft_atod(l_split[3]) / 2.0;
		o->color = get_color(d, l_split[4]);
		o->shininess = ft_atod(l_split[5]);
		o->shape.sphere.rotation = 0.0;
		o->shape.sphere.rotation_speed = ft_atod(l_split[6]);
		if (ft_strncmp(l_split[9], "NULL", 5))
		{
			if (ft_strncmp(l_split[10], "NULL", 5))
				pars_texture_map(d, &(o->texture), l_split[9], l_split[10]);
			else
				pars_texture_map(d, &(o->texture), l_split[9], NULL);
		}
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0 || o->shininess <= 0.0)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

/*	<Identifier> <Name> <Normal> <InnerRadius> <OuterRadius>
	<Color> <Shininess> <Texture> <Bumpmap>	*/
void	add_ri(t_data *d, t_object *o, char **l_split, int idx)
{
	if (check_idx_string_tab(l_split, 8))
	{
		if (!double_valid(l_split[3]) || !double_valid(l_split[4])
			|| !double_valid(l_split[6]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		o->type = OBJ_RING;
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
		o->shininess = ft_atod(l_split[6]);
		if (ft_strncmp(l_split[7], "NULL", 5))
		{
			if (ft_strncmp(l_split[8], "NULL", 5))
				pars_texture_map(d, &(o->texture), l_split[7], l_split[8]);
			else
				pars_texture_map(d, &(o->texture), l_split[7], NULL);
		}
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
	if (o->shape.ring.inner_rad < 0.0
		|| o->shape.ring.outer_rad <= o->shape.ring.inner_rad
		|| o->shape.ring.center == NULL || o->shininess <= 0.0)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
}

/*	<Identifier> <Name> <Position> <Diameter> <Color> <Shininess> <Intensity>
	<Mass> <Velocity> <Texture> <Bumpmap> -- mass/velocity not wired
	yet.	*/
void	add_so(t_data *d, t_sun *s, char **l)
{
	if (check_idx_string_tab(l, 10))
	{
		if (!double_valid(l[3]) || !double_valid(l[5]) || !double_valid(l[6]))
			exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
		s->name = get_name(l[1]);
		s->pos = get_vec(d, l[2]);
		s->radius = ft_atod(l[3]) / 2.0;
		s->color = get_color(d, l[4]);
		s->shininess = ft_atod(l[5]);
		s->intensity = ft_atod(l[6]);
		if (ft_strncmp(l[9], "NULL", 5))
		{
			if (ft_strncmp(l[10], "NULL", 5))
				pars_texture_map(d, &(s->texture), l[9], l[10]);
			else
				pars_texture_map(d, &(s->texture), l[9], NULL);
		}
	}
	else
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
	if (s->radius <= 0.0 || s->intensity < 0 || s->shininess <= 0.0)
		exit_prog(d, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
}
