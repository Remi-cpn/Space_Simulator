/* ************************************************************************** */
/*   Space_Simulator — init_hud.c                                             */
/*   Construit l'arbre de valeurs navigable/reglable du HUD (categories ->    */
/*   valeurs), a appeler une fois que d->sim est en place (apres parsing).    */
/* ************************************************************************** */

#include "../data.h"
#include "../debug/debug.h"

static void	init_hud_params(t_data *d, t_hud_db *cat)
{
	hud_append(&cat->child, hud_new(d, "rayons/px", HUD_UINT, &d->nbr_ray));
	hud_append(&cat->child, hud_new(d, "coef molette", HUD_UINT, &d->wheel_coef));
}

static void	init_hud_blackhole(t_data *d, t_hud_db *cat)
{
	hud_append(&cat->child, hud_new(d, "masse", HUD_FLOAT, &d->sim.bh.mass));
	hud_append(&cat->child, hud_new(d, "pos x", HUD_DOUBLE, &d->sim.bh.pos.x));
	hud_append(&cat->child, hud_new(d, "pos y", HUD_DOUBLE, &d->sim.bh.pos.y));
	hud_append(&cat->child, hud_new(d, "pos z", HUD_DOUBLE, &d->sim.bh.pos.z));
}

static void	init_hud_camera(t_data *d, t_hud_db *cat)
{
	hud_append(&cat->child, hud_new(d, "fov", HUD_DOUBLE, &d->sim.cam.fov));
	hud_append(&cat->child, hud_new(d, "pos x", HUD_DOUBLE, &d->sim.cam.origin.x));
	hud_append(&cat->child, hud_new(d, "pos y", HUD_DOUBLE, &d->sim.cam.origin.y));
	hud_append(&cat->child, hud_new(d, "pos z", HUD_DOUBLE, &d->sim.cam.origin.z));
	hud_append(&cat->child, hud_new(d, "dir x", HUD_DOUBLE, &d->sim.cam.dir.x));
	hud_append(&cat->child, hud_new(d, "dir y", HUD_DOUBLE, &d->sim.cam.dir.y));
	hud_append(&cat->child, hud_new(d, "dir z", HUD_DOUBLE, &d->sim.cam.dir.z));
}

// Categorie "Objets" laissee vide (pas de child) : nb_obj vaut toujours 0
// tant que la v2 (parsing d'objets) n'existe pas -> sert de premier vrai
// test pour le garde-fou "categorie vide" prevu cote navigation.
void	init_hud(t_data *d)
{
	t_hud_db	*cat;

	d->hud_db = NULL;
	cat = hud_new(d, "Parametres (touches)", HUD_NONE, NULL);
	hud_append(&d->hud_db, cat);
	init_hud_params(d, cat);
	cat = hud_new(d, "Trou noir", HUD_NONE, NULL);
	hud_append(&d->hud_db, cat);
	init_hud_blackhole(d, cat);
	cat = hud_new(d, "Objets", HUD_NONE, NULL);
	hud_append(&d->hud_db, cat);
	cat = hud_new(d, "Camera", HUD_NONE, NULL);
	hud_append(&d->hud_db, cat);
	init_hud_camera(d, cat);
	print_hud(d, NULL);
}
