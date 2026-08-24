/* ************************************************************************** */
/*   Space_Simulator — hud.c                                                  */
/*   Affichage debug en direct dans le terminal.                              */
/* ************************************************************************** */

#include "debug.h"
#include <stdio.h>

# define YELLOW_BOLD "\033[1;33m"
# define HIGHLIGHT   "\033[7m"
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

// Cas particulier : les objets de scene ne sont pas encore des noeuds de
// l'arbre (pas de v2 pour l'instant), donc pas ciblables/surlignables comme
// le reste. A retirer le jour ou ils deviennent de vrais enfants de la
// categorie "Objets".
static int	print_scene_objects(t_data *d)
{
	int	i;

	if (d->sim.nb_obj == 0)
	{
		printf("\033[2K\r - (aucun)\n");
		return (1);
	}
	i = 0;
	while (i < d->sim.nb_obj)
	{
		printf("\033[2K\r - %s\n", obj_type_name(d->sim.objs[i].type));
		i++;
	}
	return (d->sim.nb_obj);
}

// ft_printf (libft) ne gère pas %f -> printf standard utilisé ici.
static void	print_leaf(t_hud_db *node, t_hud_db *target)
{
	const char	*hl;
	const char	*rst;

	hl = (node == target) ? HIGHLIGHT : "";
	rst = (node == target) ? RESET : "";
	if (node->tag == HUD_UINT)
		printf("\033[2K\r%s - %s : %u%s\n", hl, node->name, *node->u_value_ptr.u, rst);
	else if (node->tag == HUD_INT)
		printf("\033[2K\r%s - %s : %d%s\n", hl, node->name, *node->u_value_ptr.i, rst);
	else if (node->tag == HUD_FLOAT)
		printf("\033[2K\r%s - %s : %.2f%s\n", hl, node->name, *node->u_value_ptr.f, rst);
	else if (node->tag == HUD_DOUBLE)
		printf("\033[2K\r%s - %s : %.2f%s\n", hl, node->name, *node->u_value_ptr.d, rst);
}

// Affiche une categorie (surlignee si elle est la cible) puis parcourt ses
// enfants dans l'arbre -> generique, rien a retoucher ici si on ajoute une
// valeur dans init_hud.c.
static int	print_category(t_data *d, t_hud_db *cat, t_hud_db *target)
{
	t_hud_db	*child;
	int			lines;

	if (cat == target)
		printf("\033[2K\r" HIGHLIGHT YELLOW_BOLD "%s" RESET "\n", cat->name);
	else
		printf("\033[2K\r" YELLOW_BOLD "%s" RESET "\n", cat->name);
	lines = 1;
	child = cat->child;
	while (child)
	{
		print_leaf(child, target);
		lines++;
		child = child->next;
	}
	if (ft_strncmp(cat->name, "Objets", 7) == 0)
		lines += print_scene_objects(d);
	return (lines);
}

// \033[2K efface la ligne courante, \033[NA remonte le curseur de N lignes :
// reecriture propre meme si le nombre de lignes change (arbre plus profond,
// objets en plus...), calcule dynamiquement a chaque appel.
void	print_hud(t_data *d, t_hud_db *target)
{
	static int	prev_lines = 0;
	int			lines;
	t_hud_db	*cat;

	if (prev_lines > 0)
		printf("\033[%dA", prev_lines);
	printf("\033[2K\r" YELLOW_BOLD "Target" RESET " : %s\n",
		target ? target->name : "(aucune)");
	lines = 1;
	cat = d->hud_db;
	while (cat)
	{
		lines += print_category(d, cat, target);
		cat = cat->next;
	}
	prev_lines = lines;
	fflush(stdout);
}
