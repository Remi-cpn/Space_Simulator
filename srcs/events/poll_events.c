/* ************************************************************************** */
/*   Space_Simulator — poll_events.c                                          */
/* ************************************************************************** */

#include "events.h"
#include "../data.h"

static bool	set_input(t_data *d, t_input *input, int scancode, bool value, int flag)
{
	//ft_printf("%d\n", scancode);
	switch (scancode)
	{
		case W : input->w = value; break;
		case A : input->a = value; break;
		case S : input->s = value; break;
		case D : input->d = value; break;

		case UP : input->up = value; break;
		case DOWN : input->down = value; break;
		case LEFT : input->left = value; break;
		case RIGHT : input->right = value; break;

		case LCTRL : input->ctrl = value; break;
		case SPACE : input->space = value; break;

		case PGUP : d->nbr_ray += flag; break;
		case PGDOWN : d->nbr_ray = (d->nbr_ray == 1) ? d->nbr_ray : d->nbr_ray - flag; break;

		case ESC : return false;

		default : break;
	}
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
		// Key events
		if (ev.type == SDL_KEYDOWN)
			continu = set_input(d, &(d->input), ev.key.keysym.scancode, true, 1);
		else if (ev.type == SDL_KEYUP)
			continu = set_input(d, &(d->input), ev.key.keysym.scancode, false, 0);

		// Event sur la windows
		if (ev.type == SDL_WINDOWEVENT)
			continu = window_event(d, ev);

		// Fentre fermee par la croix
		if (ev.type == SDL_QUIT)
			continu = false;
	}
	return continu;
}