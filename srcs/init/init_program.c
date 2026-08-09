/* ************************************************************************** */
/*   Space_Simulator — init_program.c                                         */
/* ************************************************************************** */

#include "includes/data.h"
#include "includes/exit.h"

static t_input	init_input(void)
{
	t_input	i;

	ft_memset(&i, 0, sizeof(t_input));
	return (i);
}

static void	init_SDL(t_data *d)
{
	// Initialisation du système vidéo
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_prog(d, ERROR_SDL_INIT, SDL_GetError());

	// Choix de la version de SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Choix du profil
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	// Pour un rendu hors écran
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Initialisation de la fenêtre
	d->win = SDL_CreateWindow("Space_Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_OPENGL);
	if (!d->win)
		exit_prog(d, ERROR_SDL_WINDOW, SDL_GetError());

	// Initialisation du context, l'état complet d'OpenGL
	d->ctx = SDL_GL_CreateContext(d->win);
	if (!d->ctx)
		exit_prog(d, ERROR_SDL_CONTEXT, SDL_GetError());
}

t_data	init_program(void)
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	init_SDL(&d);
	d.input = init_input();
	d.cam_target = -1;
	return (d);
}