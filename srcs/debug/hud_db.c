/* ************************************************************************** */
/*   Space_Simulator — hud_db.c                                               */
/*   Briques de base pour construire l'arbre de valeurs navigable du HUD.     */
/* ************************************************************************** */

#include "debug.h"
#include "../exit/exit.h"

// current = noeud vise (une categorie si on est au niveau racine, une
// valeur si on est rentre dans une categorie).
// category = la categorie dans laquelle on est rentre, pour pouvoir y
// revenir avec BACK (pas de pointeur "parent" dans t_hud_db, donc on
// retient simplement d'ou on vient).
t_hud_db	*hud_select(t_data *d, t_key key)
{
	static t_hud_db	*current = NULL;
	static t_hud_db	*category = NULL;
	static bool		in_category = false;

	if (!current)
		current = d->hud_db;
	if (key == TAB)
		current = current->next ? current->next : current->head;
	else if (key == ENTER && !in_category && current->child)
	{
		category = current;
		current = current->child;
		in_category = true;
	}
	else if (key == BACK && in_category)
	{
		current = category;
		in_category = false;
	}
	return (current);
}

t_hud_db	*hud_new(t_data *d, char *name, t_tag tag, void *ptr)
{
	t_hud_db	*node;

	node = ft_calloc(1, sizeof(t_hud_db));
	if (!node)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	node->name = name;
	node->tag = tag;
	if (tag == HUD_UINT)
		node->u_value_ptr.u = ptr;
	else if (tag == HUD_INT)
		node->u_value_ptr.i = ptr;
	else if (tag == HUD_FLOAT)
		node->u_value_ptr.f = ptr;
	else if (tag == HUD_DOUBLE)
		node->u_value_ptr.d = ptr;
	return (node);
}

void	hud_append(t_hud_db **head, t_hud_db *new_node)
{
	t_hud_db	*last;

	if (!*head)
	{
		*head = new_node;
		new_node->head = new_node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->head = *head;
}
