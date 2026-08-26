/* ************************************************************************** */
/*   Space_Simulator — init_hud.c                                             */
/*   Construit l'arbre de valeurs navigable/reglable du HUD (categories ->    */
/*   instances nommees -> parametres), a appeler une fois que d->sim est en   */
/*   place (apres parsing).                                                   */
/* ************************************************************************** */

#include "../data.h"
#include "../debug/debug.h"

static char	*label(char *name)
{
	if (name)
		return (name);
	return ("(sans nom)");
}

// Enregistre dans l'arbre les parametres reglables au clavier/molette
// (nombre de rayons, coefficient de vitesse, exposure/gamma).
static void	init_hud_params(t_data *d, t_hud_db *cat)
{
	hud_append(cat, &cat->child, hud_new(d, "rayons/px", HUD_UINT, &d->nbr_ray));
	hud_append(cat, &cat->child, hud_new(d, "coef molette", HUD_UINT, &d->wheel_coef));
	hud_append(cat, &cat->child, hud_new(d, "exposure", HUD_FLOAT, &d->exposure));
	hud_append(cat, &cat->child, hud_new(d, "gamma", HUD_FLOAT, &d->gamma));
}

// Une sous-categorie par trou noir, nommee, avec masse/position en enfants.
static void	init_hud_blackholes(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;
	int			i;

	i = 0;
	while (i < d->sim.nb_bh)
	{
		inst = hud_new(d, label(d->sim.blackholes[i].name), HUD_NONE, NULL);
		hud_append(cat, &cat->child, inst);
		hud_append(inst, &inst->child, hud_new(d, "masse", HUD_FLOAT,
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

// Une sous-categorie par soleil, nommee, avec rayon/intensite en enfants.
static void	init_hud_suns(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;
	int			i;

	i = 0;
	while (i < d->sim.nb_sun)
	{
		inst = hud_new(d, label(d->sim.suns[i].name), HUD_NONE, NULL);
		hud_append(cat, &cat->child, inst);
		hud_append(inst, &inst->child, hud_new(d, "rayon", HUD_DOUBLE,
				&d->sim.suns[i].radius));
		hud_append(inst, &inst->child, hud_new(d, "intensite", HUD_DOUBLE,
				&d->sim.suns[i].intensity));
		i++;
	}
}

// Une sous-categorie par objet (sphere/anneau), nommee, avec les champs
// propres a son type en enfants.
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
		hud_append(inst, &inst->child, hud_new(d, "rayon", HUD_DOUBLE,
				&o->shape.sphere.radius));
		hud_append(inst, &inst->child, hud_new(d, "rotation speed",
				HUD_DOUBLE, &o->shape.sphere.rotation_speed));
	}
	else if (o->type == OBJ_RING)
	{
		hud_append(inst, &inst->child, hud_new(d, "rayon int", HUD_DOUBLE,
				&o->shape.ring.inner_rad));
		hud_append(inst, &inst->child, hud_new(d, "rayon ext", HUD_DOUBLE,
				&o->shape.ring.outer_rad));
	}
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

// Une sous-categorie par lumiere, nommee, avec position/intensite.
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
		hud_append(inst, &inst->child, hud_new(d, "intensite", HUD_DOUBLE,
				&d->sim.lights[i].intensity));
		i++;
	}
}

// Meme structure que les autres categories (instance -> parametres),
// meme s'il n'y a qu'un seul mode caméra pour l'instant ("Libre", le
// seul implemente dans camera.c) : pret pour d'autres modes plus tard
// (ex. "Follow") sans rien changer ici.
static void	init_hud_camera(t_data *d, t_hud_db *cat)
{
	t_hud_db	*inst;

	inst = hud_new(d, "Libre", HUD_NONE, NULL);
	hud_append(cat, &cat->child, inst);
	hud_append(inst, &inst->child, hud_new(d, "fov", HUD_DOUBLE, &d->sim.cam.fov));
	hud_append(inst, &inst->child, hud_new(d, "pos x", HUD_DOUBLE, &d->sim.cam.origin.x));
	hud_append(inst, &inst->child, hud_new(d, "pos y", HUD_DOUBLE, &d->sim.cam.origin.y));
	hud_append(inst, &inst->child, hud_new(d, "pos z", HUD_DOUBLE, &d->sim.cam.origin.z));
	hud_append(inst, &inst->child, hud_new(d, "dir x", HUD_DOUBLE, &d->sim.cam.dir.x));
	hud_append(inst, &inst->child, hud_new(d, "dir y", HUD_DOUBLE, &d->sim.cam.dir.y));
	hud_append(inst, &inst->child, hud_new(d, "dir z", HUD_DOUBLE, &d->sim.cam.dir.z));
}

// Construit l'arbre HUD complet et l'affiche une premiere fois. Chaque
// categorie racine reste vide (affichee "(aucun)") si la scene n'a rien
// de ce type.
void	init_hud(t_data *d)
{
	t_hud_db	*cat;

	d->hud_db = NULL;
	cat = hud_new(d, "Reglage", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_params(d, cat);
	cat = hud_new(d, "Trou noir", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_blackholes(d, cat);
	cat = hud_new(d, "Soleil", HUD_NONE, NULL);
	hud_append(NULL, &d->hud_db, cat);
	init_hud_suns(d, cat);
	cat = hud_new(d, "Objets", HUD_NONE, NULL);
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
