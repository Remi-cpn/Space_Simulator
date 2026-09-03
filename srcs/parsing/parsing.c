/* ************************************************************************** */
/*   Space_Simulator — parsing.c                                              */
/*   Entry point for scene loading : validates the file, allocates the        */
/*   scene arrays, parses the file, then uploads/initializes everything.      */
/* ************************************************************************** */

#include "parsing.h"
#include "../exit/exit.h"
#include "../shaders/shader.h"

/*	Calculates the number of objects in the scene for memory
	allocation.	*/
static int	init_nb_obj(t_data *d, int nb_light, int nb_sun, int nb_bh,
	int count_line)
{
	int	nb_obj;
	int	reserved;

	nb_obj = 0;
	reserved = 2 + nb_light + nb_sun + nb_bh;
	if (count_line < 3)
		exit_prog(d, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	else if (count_line == reserved)
		nb_obj = 0;
	else
		nb_obj = count_line - reserved;
	return (nb_obj);
}

/*	Checks the validity of the file extension.	*/
static int	check_file_name(t_data *d, char *file_name)
{
	if (check_extention(file_name, ".ss") == true)
	{
		d->ss_file = true;
		return (1);
	}
	return (0);
}

/*	Builds the scene (camera, black hole still hardcoded for now),
	then initializes the viewport, HUD tree and skybox.	*/
void	parsing(t_data *d, char *file_name)
{
	int	count_l;

	if (!check_file_name(d, file_name))
		exit_prog(d, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);

	count_l = count_line(d, file_name);
	d->sim.nb_obj = init_nb_obj(d, d->sim.nb_light, d->sim.nb_sun,
			d->sim.nb_bh, count_l);

	d->sim.lights = ft_calloc(d->sim.nb_light, sizeof(t_light));
	d->sim.suns = ft_calloc(d->sim.nb_sun, sizeof(t_sun));
	d->sim.blackholes = ft_calloc(d->sim.nb_bh, sizeof(t_blackhole));
	if (d->sim.nb_obj > 0)
		d->sim.objs = ft_calloc(d->sim.nb_obj, sizeof(t_object));
	if (!d->sim.lights || !d->sim.suns || !d->sim.blackholes
		|| (d->sim.nb_obj > 0 && !d->sim.objs))
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);

	pars_file(d, file_name, d->ss_file);

	// Uploads the objects to the GPU (once only, static scene for v2)
	upload_sphere_buffer(d);
	upload_ring_buffer(d);
	upload_light_buffer(d);
	upload_blackhole_buffer(d);

	// Simulation struct initialization
	init_sim(d);
	init_hud(d);
	d->sim.sky.tex = load_texture(d, "assets/textures/skybox.jpg");
}
