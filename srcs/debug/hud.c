/* ************************************************************************** */
/*   Space_Simulator — hud.c                                                  */
/*   Live debug display in the terminal.                                      */
/* ************************************************************************** */

#include "debug.h"
#include <stdio.h>

/*	Prints just the value, highlighted if this exact node is the target.	*/
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

/*	Compares the first len characters of a and b (used by is_vec3 to
	check that 3 fields share the same prefix).	*/
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

/*	Detects three consecutive fields "prefix x"/"prefix y"/"prefix z"
	(same prefix, same length) to group them for display
	("pos x"/"pos y"/"pos z" -> "pos {..}").	*/
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

/*	Prints "prefix {vx, vy, vz}", each component individually
	highlighted if it is the target.	*/
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

/*	Prints "name : value" for a plain field (no vec3 grouping).	*/
static void	print_field_inline(t_hud_db *node, t_hud_db *target)
{
	printf("%s : ", node->name);
	print_value_only(node, target);
}

/*	A plain value ("flat" categories like Settings/Camera) : one line
	per field, or per pos/dir {x, y, z} group. Returns the next node to
	process (skips 3 slots if a group was just consumed).	*/
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

/*	A named instance (black hole/sun/object/light) : a single line, its
	name then all its fields in a row separated by " | " (pos/dir
	triplets grouped as {x, y, z}).	*/
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

/*	Prints a category (highlighted if targeted) then its children :
	either named instances (tag HUD_NONE, one summary line each), or
	direct values (one line per field/group) -> generic, nothing to
	touch here if a category or field is added in init_hud.c.	*/
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
		printf("\033[2K\r - (none)\n");
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

/*	\033[2K clears the current line, \033[NA moves the cursor up N
	lines : a clean rewrite even if the number of lines changes. The
	whole tree stays displayed at all times. Highlighting shows the
	current target.	*/
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
