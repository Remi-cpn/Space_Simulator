/* ************************************************************************** */
/*   Space_Simulator — init_hud.c                                             */
/*   Builds the HUD's navigable/editable value tree (categories ->            */
/*   named instances -> parameters).                                          */
/* ************************************************************************** */

#include "../data.h"
#include "debug.h"

static char	*label(char *name)
{
	if (name)
		return (name);
	return ("(no name)");
}

/*	Registers the parameters adjustable via keyboard/wheel into
	the tree.	*/
static void	init_hud_params(t_data *d, t_hud_db *cat)
{
	hud_append(cat, &cat->child, hud_new(d, "rays/px", HUD_UINT, &d->nbr_ray));
	hud_append(cat, &cat->child, hud_new(d, "wheel coef", HUD_UINT, &d->wheel_coef));
	hud_append(cat, &cat->child, hud_new(d, "exposure", HUD_FLOAT, &d->exposure));
	hud_append(cat, &cat->child, hud_new(d, "gamma", HUD_FLOAT, &d->gamma));
	hud_append(cat, &cat->child, hud_new(d, "shadow dist", HUD_FLOAT,
			&d->sim.shadow_dist));
	hud_append(cat, &cat->child, hud_new(d, "steps", HUD_INT, &d->steps));
	hud_append(cat, &cat->child, hud_new(d, "step size", HUD_FLOAT,
			&d->step_size));
	hud_append(cat, &cat->child, hud_new(d, "ambient ratio", HUD_DOUBLE,
			&d->sim.ambient_ratio));
	hud_append(cat, &cat->child, hud_new(d, "ambient r", HUD_INT,
			&d->sim.ambient.r));
	hud_append(cat, &cat->child, hud_new(d, "ambient g", HUD_INT,
			&d->sim.ambient.g));
	hud_append(cat, &cat->child, hud_new(d, "ambient b", HUD_INT,
			&d->sim.ambient.b));
}

/*	One named sub-category per black hole, with mass/position as
	children.	*/
static void	init_hud_blackholes(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;
	int			i;

	i = 0;
	while (i < d->sim.nb_bh)
	{
		inst = hud_new(d, label(d->sim.blackholes[i].name), HUD_NONE, NULL);
		hud_append(cat, &cat->child, inst);
		hud_append(inst, &inst->child, hud_new(d, "mass", HUD_FLOAT,
				&d->sim.blackholes[i].mass));
		hud_append(inst, &inst->child, hud_new(d, "pos x", HUD_DOUBLE,
				&d->sim.blackholes[i].pos.x));
		hud_append(inst, &inst->child, hud_new(d, "pos y", HUD_DOUBLE,
				&d->sim.blackholes[i].pos.y));
		hud_append(inst, &inst->child, hud_new(d, "pos z", HUD_DOUBLE,
				&d->sim.blackholes[i].pos.z));
		i++;
	}
}

/*	One named sub-category per sun, with radius/intensity as
	children.	*/
static void	init_hud_suns(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;
	int			i;

	i = 0;
	while (i < d->sim.nb_sun)
	{
		inst = hud_new(d, label(d->sim.suns[i].name), HUD_NONE, NULL);
		hud_append(cat, &cat->child, inst);
		hud_append(inst, &inst->child, hud_new(d, "radius", HUD_DOUBLE,
				&d->sim.suns[i].radius));
		hud_append(inst, &inst->child, hud_new(d, "intensity", HUD_DOUBLE,
				&d->sim.suns[i].intensity));
		hud_append(inst, &inst->child, hud_new(d, "shininess", HUD_DOUBLE,
				&d->sim.suns[i].shininess));
		i++;
	}
}

/*	One named sub-category per object (sphere/ring), with the fields
	specific to its type as children.	*/
static void	init_hud_object(t_data *d, t_hud_db *cat, t_object *o)
{
	t_hud_db	*inst;

	inst = hud_new(d, label(o->name), HUD_NONE, NULL);
	hud_append(cat, &cat->child, inst);
	if (o->type == OBJ_SPHERE)
	{
		hud_append(inst, &inst->child, hud_new(d, "pos x", HUD_DOUBLE,
				&o->shape.sphere.center.x));
		hud_append(inst, &inst->child, hud_new(d, "pos y", HUD_DOUBLE,
				&o->shape.sphere.center.y));
		hud_append(inst, &inst->child, hud_new(d, "pos z", HUD_DOUBLE,
				&o->shape.sphere.center.z));
		hud_append(inst, &inst->child, hud_new(d, "radius", HUD_DOUBLE,
				&o->shape.sphere.radius));
	}
	else if (o->type == OBJ_RING)
	{
		hud_append(inst, &inst->child, hud_new(d, "inner radius", HUD_DOUBLE,
				&o->shape.ring.inner_rad));
		hud_append(inst, &inst->child, hud_new(d, "outer radius", HUD_DOUBLE,
				&o->shape.ring.outer_rad));
	}
	hud_append(inst, &inst->child, hud_new(d, "shininess", HUD_DOUBLE,
			&o->shininess));
}

static void	init_hud_objects(t_data *d, t_hud_db *cat)
{
	int	i;

	i = 0;
	while (i < d->sim.nb_obj)
	{
		init_hud_object(d, cat, &d->sim.objs[i]);
		i++;
	}
}

/*	One named sub-category per light, with position/intensity.	*/
static void	init_hud_lights(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;
	int			i;

	i = 0;
	while (i < d->sim.nb_light)
	{
		inst = hud_new(d, label(d->sim.lights[i].name), HUD_NONE, NULL);
		hud_append(cat, &cat->child, inst);
		hud_append(inst, &inst->child, hud_new(d, "pos x", HUD_DOUBLE,
				&d->sim.lights[i].position.x));
		hud_append(inst, &inst->child, hud_new(d, "pos y", HUD_DOUBLE,
				&d->sim.lights[i].position.y));
		hud_append(inst, &inst->child, hud_new(d, "pos z", HUD_DOUBLE,
				&d->sim.lights[i].position.z));
		hud_append(inst, &inst->child, hud_new(d, "intensity", HUD_DOUBLE,
				&d->sim.lights[i].intensity));
		i++;
	}
}

/*	Same structure as the other categories (instance -> parameters),
	even though there is only one camera mode for now ("Free", the
	only one implemented in camera.c) : ready for other modes later
	(e.g. "Follow") without changing anything here.	*/
static void	init_hud_camera(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;

	inst = hud_new(d, "Free", HUD_NONE, NULL);
	hud_append(cat, &cat->child, inst);
	hud_append(inst, &inst->child, hud_new(d, "fov", HUD_DOUBLE, &d->sim.cam.fov));
	hud_append(inst, &inst->child, hud_new(d, "pos x", HUD_DOUBLE, &d->sim.cam.origin.x));
	hud_append(inst, &inst->child, hud_new(d, "pos y", HUD_DOUBLE, &d->sim.cam.origin.y));
	hud_append(inst, &inst->child, hud_new(d, "pos z", HUD_DOUBLE, &d->sim.cam.origin.z));
	hud_append(inst, &inst->child, hud_new(d, "dir x", HUD_DOUBLE, &d->sim.cam.dir.x));
	hud_append(inst, &inst->child, hud_new(d, "dir y", HUD_DOUBLE, &d->sim.cam.dir.y));
	hud_append(inst, &inst->child, hud_new(d, "dir z", HUD_DOUBLE, &d->sim.cam.dir.z));
}

/*	Builds the complete HUD tree and prints it for the first time.
	Each root category stays empty (shown as "(none)") if the scene
	has nothing of that type.	*/
void	init_hud(t_data *d)
{
	t_hud_db	*cat;

	d->hud_db = NULL;
	cat = hud_new(d, "Settings", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_params(d, cat);
	cat = hud_new(d, "Black hole", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_blackholes(d, cat);
	cat = hud_new(d, "Sun", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_suns(d, cat);
	cat = hud_new(d, "Objects", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_objects(d, cat);
	cat = hud_new(d, "Lights", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_lights(d, cat);
	cat = hud_new(d, "Camera", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_camera(d, cat);
	print_hud(d, hud_select(d, NONE));
}
