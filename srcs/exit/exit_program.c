/* ************************************************************************** */
/*   Space_Simulator — exit_program.c                                         */
/*   Frees GL/SDL/scene/HUD resources (SSBOs, textures, HUD tree), prints an  */
/*   error if given, then exits with the right status code.                   */
/* ************************************************************************** */

#include "exit.h"
#include "../debug/debug.h"

/*	Frees the object SSBOs.	*/
static void	free_ssbo(t_data *d)
{
	if (d->sphere_ssbo)
		glDeleteBuffers(1, &(d->sphere_ssbo));
	if (d->ring_ssbo)
		glDeleteBuffers(1, &(d->ring_ssbo));
	if (d->light_ssbo)
		glDeleteBuffers(1, &(d->light_ssbo));
	if (d->blackhole_ssbo)
		glDeleteBuffers(1, &(d->blackhole_ssbo));
}

/*	Frees the scene arrays ; each entity may carry an allocated name
	that must be freed before the array that holds it.	*/
static void	free_sim_entities(t_data *d)
{
	int	i;

	i = 0;
	if (d->sim.objs)
	{
		while (i < d->sim.nb_obj)
			free(d->sim.objs[i++].name);
		free(d->sim.objs);
	}
	i = 0;
	if (d->sim.suns)
	{
		while (i < d->sim.nb_sun)
			free(d->sim.suns[i++].name);
		free(d->sim.suns);
	}
	i = 0;
	if (d->sim.blackholes)
	{
		while (i < d->sim.nb_bh)
			free(d->sim.blackholes[i++].name);
		free(d->sim.blackholes);
	}
	i = 0;
	if (d->sim.lights)
	{
		while (i < d->sim.nb_light)
			free(d->sim.lights[i++].name);
		free(d->sim.lights);
	}
}

/*	Frees the HUD tree : descends via "child" and advances via "next",
	never via parent or head.	*/
static void	free_hud_tree(t_hud_db *node)
{
	t_hud_db	*next;

	while (node)
	{
		free_hud_tree(node->child);
		next = node->next;
		free(node);
		node = next;
	}
}

/*	Cleanly frees the GL/SDL/scene/HUD resources, prints an error
	message if given, then exits with the right status code.	*/
void	exit_prog(t_data *d, int exit_code, const char *error_message)
{
	int	i;

	if (error_message)
		ft_print_error((char *)error_message);

	if (d->ctx)
		SDL_GL_DeleteContext(d->ctx);
	if (d->win)
		SDL_DestroyWindow(d->win);
	if (d->fbo)
		glDeleteFramebuffers(1, &(d->fbo));
	if (d->img)
		glDeleteTextures(1, &(d->img));
	if (d->program)
		glDeleteProgram(d->program);
	free_ssbo(d);
	if (d->tex)
	{
		i = 0;
		while (i < d->tex_count)
		{
			free(d->tex[i].path);
			glDeleteTextures(1, &(d->tex[i].id));
			i++;
		}
		free(d->tex);
	}
	free_sim_entities(d);
	free_hud_tree(d->hud_db);
	SDL_Quit();

	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}
