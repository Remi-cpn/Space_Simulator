/* ************************************************************************** */
/*   Space_Simulator — poll_events.c                                          */
/* ************************************************************************** */

#include "events.h"
#include "../data.h"

static bool	key_event(t_data *d, SDL_Event ev)
{
	(void)d;
	// Fenetre fermee par key
	if (ev.key.keysym.sym == SDLK_ESCAPE)
		return false;
	return true;
}

static bool	window_event(t_data *d, SDL_Event ev)
{
	// Gestionnaire de resize
	if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
		init_resize_image(d, ev.window.data1, ev.window.data2);
	return true;
}

bool	lisen_poll_event(t_data *d)
{
	SDL_Event	ev;
	bool		continu;

	continu = true;
	while (SDL_PollEvent(&ev))
	{
		// Fenetre fermee par key
		if (ev.type == SDL_KEYDOWN)
			continu = key_event(d, ev);
		// Event sur la windows
		if (ev.type == SDL_WINDOWEVENT)
			continu = window_event(d, ev);
		// Fentre fermee par la croix
		if (ev.type == SDL_QUIT)
			continu = false;
	}
	return continu;
}