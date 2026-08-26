/* ************************************************************************** */
/*   Space_Simulator — hud.c                                                  */
/*   Affichage debug en direct dans le terminal.                              */
/* ************************************************************************** */

#include "debug.h"
#include <stdio.h>

# define YELLOW_BOLD "\033[1;33m"
# define HIGHLIGHT   "\033[7m"
# define RESET       "\033[0m"

// ft_printf (libft) ne gère pas %f -> printf standard utilisé ici.
// Affiche juste la valeur (pas de nom), surlignee si ce noeud precis
// est la cible.
static void	print_value_only(t_hud_db *node, t_hud_db *target)
{
	const char	*hl;
	const char	*rst;

	hl = (node == target) ? HIGHLIGHT : "";
	rst = (node == target) ? RESET : "";
	if (node->tag == HUD_UINT)
		printf("%s%u%s", hl, *node->u_value_ptr.u, rst);
	else if (node->tag == HUD_INT)
		printf("%s%d%s", hl, *node->u_value_ptr.i, rst);
	else if (node->tag == HUD_FLOAT)
		printf("%s%.2f%s", hl, *node->u_value_ptr.f, rst);
	else if (node->tag == HUD_DOUBLE)
		printf("%s%.2f%s", hl, *node->u_value_ptr.d, rst);
}

static int	same_prefix(char *a, char *b, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

// Detecte trois champs consecutifs "prefixe x"/"prefixe y"/"prefixe z"
// (meme prefixe, meme longueur) pour les regrouper a l'affichage
// ("pos x"/"pos y"/"pos z" -> "pos {..}", pareil pour "dir").
static int	is_vec3(t_hud_db *x)
{
	int			len;
	t_hud_db	*y;
	t_hud_db	*z;

	len = ft_strlen(x->name);
	if (len < 2 || x->name[len - 1] != 'x' || x->name[len - 2] != ' ')
		return (0);
	y = x->next;
	z = y ? y->next : NULL;
	if (!y || !z || (int)ft_strlen(y->name) != len
		|| (int)ft_strlen(z->name) != len)
		return (0);
	if (y->name[len - 1] != 'y' || z->name[len - 1] != 'z')
		return (0);
	return (same_prefix(x->name, y->name, len - 1)
		&& same_prefix(x->name, z->name, len - 1));
}

// Affiche "prefixe {vx, vy, vz}" (pas de retour a la ligne), chaque
// composant surligne individuellement s'il est la cible.
static void	print_vec3(t_hud_db *x, t_hud_db *target)
{
	t_hud_db	*y;
	t_hud_db	*z;
	int			plen;

	y = x->next;
	z = y->next;
	plen = ft_strlen(x->name) - 2;
	printf("%.*s {", plen, x->name);
	print_value_only(x, target);
	printf(", ");
	print_value_only(y, target);
	printf(", ");
	print_value_only(z, target);
	printf("}");
}

static void	print_field_inline(t_hud_db *node, t_hud_db *target)
{
	printf("%s : ", node->name);
	print_value_only(node, target);
}

// Une valeur seule (categories "plates" type Reglage/Camera) : une ligne
// par champ, ou par groupe pos/dir {x, y, z}. Renvoie le prochain noeud
// a traiter (saute 3 crans si un groupe vient d'etre consomme).
static t_hud_db	*print_leaf_line(t_hud_db *node, t_hud_db *target)
{
	printf("\033[2K\r - ");
	if (is_vec3(node))
	{
		print_vec3(node, target);
		printf("\n");
		return (node->next->next->next);
	}
	print_field_inline(node, target);
	printf("\n");
	return (node->next);
}

// Une instance nommee (trou noir/soleil/objet/lumiere) : une seule ligne,
// son nom puis tous ses champs a la suite separes par " | " (les
// triplets pos/dir regroupes en {x, y, z}).
static void	print_instance(t_hud_db *inst, t_hud_db *target)
{
	t_hud_db	*field;
	const char	*hl;
	const char	*rst;

	hl = (inst == target) ? HIGHLIGHT : "";
	rst = (inst == target) ? RESET : "";
	printf("\033[2K\r - %s%s%s : ", hl, inst->name, rst);
	field = inst->child;
	while (field)
	{
		if (is_vec3(field))
		{
			print_vec3(field, target);
			field = field->next->next->next;
		}
		else
		{
			print_field_inline(field, target);
			field = field->next;
		}
		if (field)
			printf(" | ");
	}
	printf("\n");
}

// Affiche une categorie (surlignee si ciblee) puis ses enfants : soit des
// instances nommees (tag HUD_NONE, une ligne resumee chacune), soit des
// valeurs directes (une ligne par champ/groupe) -> generique, rien a
// retoucher ici si on ajoute une categorie ou un champ dans init_hud.c.
static int	print_category(t_hud_db *cat, t_hud_db *target)
{
	t_hud_db	*child;
	int			lines;

	if (cat == target)
		printf("\033[2K\r" HIGHLIGHT YELLOW_BOLD "%s" RESET "\n", cat->name);
	else
		printf("\033[2K\r" YELLOW_BOLD "%s" RESET "\n", cat->name);
	lines = 1;
	child = cat->child;
	if (!child)
	{
		printf("\033[2K\r - (aucun)\n");
		return (lines + 1);
	}
	while (child)
	{
		if (child->tag == HUD_NONE)
		{
			print_instance(child, target);
			child = child->next;
		}
		else
			child = print_leaf_line(child, target);
		lines++;
	}
	return (lines);
}

// \033[2K efface la ligne courante, \033[NA remonte le curseur de N lignes :
// reecriture propre meme si le nombre de lignes change. Tout l'arbre est
// affiche en permanence ; la surbrillance seule indique la cible actuelle.
void	print_hud(t_data *d, t_hud_db *target)
{
	static int	prev_lines = 0;
	int			lines;
	t_hud_db	*cat;

	if (prev_lines > 0)
		printf("\033[%dA", prev_lines);
	lines = 0;
	cat = d->hud_db;
	while (cat)
	{
		lines += print_category(cat, target);
		cat = cat->next;
	}
	prev_lines = lines;
	fflush(stdout);
}
