/* ************************************************************************** */
/*   Space_Simulator — hud.c                                                  */
/*   Affichage debug en direct dans le terminal (pas de vrai HUD encore).     */
/* ************************************************************************** */

#include "debug.h"
#include <stdio.h>

# define YELLOW_BOLD "\033[1;33m"
# define RESET       "\033[0m"

static const char	*obj_type_name(t_obj type)
{
	if (type == OBJ_SPHERE)
		return ("sphere");
	if (type == OBJ_PLANE)
		return ("plane");
	if (type == OBJ_CYLINDER)
		return ("cylindre");
	if (type == OBJ_CONE)
		return ("cone");
	if (type == OBJ_RING)
		return ("ring");
	if (type == OBJ_SKYBOX)
		return ("skybox");
	return ("none");
}

static void	print_params(t_data *d)
{
	printf("\033[2K\r" YELLOW_BOLD "Paramètres (touches)" RESET "\n");
	printf("\033[2K\r - rayons/px : %u\n", d->nbr_ray);
}

static void	print_blackhole(t_data *d)
{
	printf("\033[2K\r" YELLOW_BOLD "Trou noir" RESET "\n");
	printf("\033[2K\r - masse : %.2f\n", d->sim.bh.mass);
	printf("\033[2K\r - position : (%.2f, %.2f, %.2f)\n",
		d->sim.bh.pos.x, d->sim.bh.pos.y, d->sim.bh.pos.z);
}

static int	print_objects(t_data *d)
{
	int	i;

	printf("\033[2K\r" YELLOW_BOLD "Objets" RESET "\n");
	if (d->sim.nb_obj == 0)
	{
		printf("\033[2K\r - (aucun)\n");
		return (2);
	}
	i = 0;
	while (i < d->sim.nb_obj)
	{
		printf("\033[2K\r - %s\n", obj_type_name(d->sim.objs[i].type));
		i++;
	}
	return (1 + d->sim.nb_obj);
}

static void	print_camera(t_data *d)
{
	printf("\033[2K\r" YELLOW_BOLD "Caméra" RESET "\n");
	printf("\033[2K\r - position : (%.2f, %.2f, %.2f)\n",
		d->sim.cam.origin.x, d->sim.cam.origin.y, d->sim.cam.origin.z);
	printf("\033[2K\r - direction : (%.2f, %.2f, %.2f)\n",
		d->sim.cam.dir.x, d->sim.cam.dir.y, d->sim.cam.dir.z);
	printf("\033[2K\r - fov : %.1f\n", d->sim.cam.fov);
}

// ft_printf (libft) ne gère pas %f -> printf standard utilisé ici pour les floats/doubles.
// \033[2K efface la ligne courante, \033[NA remonte le curseur de N lignes :
// réécriture propre même si le nombre de lignes change (ex. nb_obj qui varie).
void	print_hud(t_data *d)
{
	static int	prev_lines = 0;
	int			lines;

	if (prev_lines > 0)
		printf("\033[%dA", prev_lines);
	print_params(d);
	print_blackhole(d);
	lines = 2 + 3;
	lines += print_objects(d);
	print_camera(d);
	lines += 4;
	prev_lines = lines;
	fflush(stdout);
}
