/* ************************************************************************** */
/*   Space_Simulator — init_program.c                                         */
/* ************************************************************************** */

#include "../simulation.h"


t_simulation	init_sim(void)
{
	t_simulation	s;
	t_skybox		sky;

	ft_memset(&s, 0, sizeof(t_simulation));
	ft_memset(&sky, 0, sizeof(t_skybox));
	s.sky = sky;
	return (s);
}
