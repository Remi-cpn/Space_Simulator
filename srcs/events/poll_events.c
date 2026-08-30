/* ************************************************************************** */
/*   Space_Simulator — poll_events.c                                          */
/*   Polls SDL input events (keyboard, wheel, window) and dispatches them to  */
/*   the right handler: camera movement, HUD navigation/editing, resize.      */
/* ************************************************************************** */

#include "events.h"
#include "../data.h"
#include "../debug/debug.h"
#include "../shaders/shader.h"

/*	Updates the movement/HUD booleans for the key received, and
	reprints the HUD if a HUD action changed something.	*/
static bool	set_input(t_data *d, int scancode, bool value)
{
	t_hud_db	*h = hud_select(d, NONE);
	t_input		*input = &(d->input);

	switch (scancode)
	{
		// Movement in the simulation
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
		case LSHIFT : input->shift = value; break;

		// Number of rays per pixel
		case PGUP : d->nbr_ray += value; break;
		case PGDOWN : d->nbr_ray = (d->nbr_ray == 1) ? d->nbr_ray : d->nbr_ray - value; break;

		// Navigation in the HUD
		case ENTER : if (value) h = hud_select(d, ENTER); break;
		case BACK : if (value) h = hud_select(d, BACK); break;
		case TAB : if (value) h = hud_select(d, TAB); break;

		// Uploads the changes made from the HUD
		case R : if (value)
			{
				upload_sphere_buffer(d);
				upload_ring_buffer(d);
				upload_light_buffer(d);
				upload_blackhole_buffer(d);
			}
			break;

		case ESC : return false;
		default : break;
	}

	print_hud(d, h);

	return true;
}

/*	Wheel: Shift adjusts the speed coefficient, otherwise adjusts
	the targeted value in the HUD tree using that coefficient.	*/
static void	set_wheel(t_data *d, int ev)
{
	t_hud_db	*h = hud_select(d, NONE);

	// Handles the Shift + wheel speed multiplier
	if (ev > 0 && d->input.shift)
		d->wheel_coef++;
	else if (ev < 0 && d->wheel_coef > 1 && d->input.shift)
		d->wheel_coef--;
	if (d->input.shift)
	{
		print_hud(d, h);
		return ;
	}

	// The wheel adjusts the targeted value in the HUD tree
	int		amount = (ev > 0) ? (int)d->wheel_coef : -(int)d->wheel_coef;

	if (h->tag == HUD_UINT && h->u_value_ptr.u == &d->wheel_coef)
	{
		if ((int)*h->u_value_ptr.u + amount >= 1
			&& (int)*h->u_value_ptr.u + amount <= 5)
			*h->u_value_ptr.u += amount;
	}
	else if (h->tag == HUD_UINT)
	{
		if (amount < 0 && *h->u_value_ptr.u == 0)
			return ;
		*h->u_value_ptr.u += amount;
	}
	else if (h->tag == HUD_INT)
		*h->u_value_ptr.i += amount;
	else if (h->tag == HUD_FLOAT)
	{
		if (amount < 0 && *h->u_value_ptr.f + amount * 0.1f < 0)
			*h->u_value_ptr.f = 0;
		else
			*h->u_value_ptr.f += amount * 0.1f;
	}
	else if (h->tag == HUD_DOUBLE)
		*h->u_value_ptr.d += amount * 0.1;

	print_hud(d, h);
}

/*	Reallocates the texture/FBO to the correct size.	*/
static void	window_event(t_data *d, SDL_Event ev)
{
	if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
		init_resize_image(d, ev.window.data1, ev.window.data2);
}

/*	Loops over all pending SDL events and dispatches them to the
	right handler.	*/
bool	lisen_poll_event(t_data *d)
{
	SDL_Event	ev;
	bool		continu = true;

	while (SDL_PollEvent(&ev))
	{
		// Key events
		if (ev.type == SDL_KEYDOWN)
			continu = set_input(d, ev.key.keysym.scancode, true);
		else if (ev.type == SDL_KEYUP)
			continu = set_input(d, ev.key.keysym.scancode, false);

		// Mouse event
		if (ev.type == SDL_MOUSEWHEEL)
			set_wheel(d, ev.wheel.y);

		// Window event
		if (ev.type == SDL_WINDOWEVENT)
			window_event(d, ev);

		// Window closed via the close button
		if (ev.type == SDL_QUIT)
			continu = false;

	}
	return continu;
}
