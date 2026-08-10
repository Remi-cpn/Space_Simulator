/* ************************************************************************** */
/*   Space_Simulator — debug.c                                                */
/* ************************************************************************** */

#include "debug.h"

void	print_error(const char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
}
