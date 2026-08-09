/* ************************************************************************** */
/*   Space_Simulator — main.c                                                 */
/* ************************************************************************** */

#include "includes/data.h"

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2 && ac != 3)
		return (1);

	d = init_program();

	(void)d;
	(void)av;
}