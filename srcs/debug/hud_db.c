/* ************************************************************************** */
/*   Space_Simulator — hud_db.c                                               */
/*   Building blocks for the HUD's navigable value tree.                      */
/* ************************************************************************** */

#include "debug.h"
#include "../exit/exit.h"

/*	Moves/returns the target node according to the key received
	(Tab/Enter/Back). Made possible by the "parent" pointer in
	t_hud_db.	*/
t_hud_db	*hud_select(t_data *d, t_key key)
{
	static t_hud_db	*current = NULL;

	if (!current)
		current = d->hud_db;
	if (key == TAB)
		current = current->next ? current->next : current->head;
	else if (key == ENTER && current->child)
		current = current->child;
	else if (key == BACK && current->parent)
		current = current->parent;
	return (current);
}

/*	Allocates a HUD tree node and wires the pointer to the real
	variable into the right union member, based on the tag.	*/
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

/*	Appends new_node at the end of the *head linked list (the
	children of "parent", or the root categories if parent is NULL),
	and sets its "head" to point at the first node of that list (so
	Tab can loop over it).	*/
void	hud_append(t_hud_db *parent, t_hud_db **head, t_hud_db *new_node)
{
	t_hud_db	*last;

	new_node->parent = parent;
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
