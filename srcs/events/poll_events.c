/* ************************************************************************** */
/*   Space_Simulator — poll_events.c                                          */
/* ************************************************************************** */

#include "events.h"
#include "../data.h"
#include "../debug/debug.h"
#include "../shaders/shader.h"

// Met a jour les booleens de deplacement/HUD selon la touche recue,
// et reimprime le HUD si une action HUD a change quelque chose.
static bool	set_input(t_data *d, t_input *input, int scancode, bool value, int flag)
{
	//ft_printf("%d\n", scancode);

	t_hud_db	*h = hud_select(d, NONE);

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
		case LSHIFT : input->shift = value; break;

		case PGUP : d->nbr_ray += flag; break;
		case PGDOWN : d->nbr_ray = (d->nbr_ray == 1) ? d->nbr_ray : d->nbr_ray - flag; break;

		case ENTER : if (value) h = hud_select(d, ENTER); break;
		case BACK : if (value) h = hud_select(d, BACK); break;
		case TAB : if (value) h = hud_select(d, TAB); break;

		// Repousse l'etat CPU courant (deja modifie par le HUD) vers les
		// buffers GPU -- pas un reparse du fichier, juste une resynchro.
		case _R : if (value)
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


// Molette : Maj ajuste le coefficient de vitesse (1 a 5), sinon
// ajuste la valeur ciblee dans l'arbre HUD avec ce coefficient.
static bool	set_wheel(t_data *d, int ev)
{
	t_hud_db	*h;
	int 		amount;

	h = hud_select(d, NONE);

	// Gestion du multiplicateur de vitesse de modification Maj + molette
	if (ev > 0 && d->input.shift)
		d->wheel_coef++;
	else if (ev < 0 && d->wheel_coef > 1 && d->input.shift)
		d->wheel_coef--;
	if (d->input.shift)
	{
		print_hud(d, h);
		return true;
	}

	// Molette : ajuste la valeur ciblee dans l'arbre HUD
	amount = (ev > 0) ? (int)d->wheel_coef : -(int)d->wheel_coef;
	if (h->tag == HUD_UINT && h->u_value_ptr.u == &d->wheel_coef)
	{
		if ((int)*h->u_value_ptr.u + amount >= 1
			&& (int)*h->u_value_ptr.u + amount <= 5)
			*h->u_value_ptr.u += amount;
	}
	else if (h->tag == HUD_UINT)
	{
		if (amount < 0 && *h->u_value_ptr.u == 0)
			return (true);
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
	return (true);
}

// Reagit aux evenements de fenetre (pour l'instant : redimensionnement
// -> reallocation de la texture/FBO a la bonne taille).
static bool	window_event(t_data *d, SDL_Event ev)
{
	// Gestionnaire de resize
	if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
		init_resize_image(d, ev.window.data1, ev.window.data2);
	return true;
}

// Boucle sur tous les evenements SDL en attente et les redirige vers
// le bon gestionnaire (clavier, molette, fenetre, fermeture).
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

		if (ev.type == SDL_MOUSEWHEEL)
			continu = set_wheel(d, ev.wheel.y);

		// Event sur la windows
		if (ev.type == SDL_WINDOWEVENT)
			continu = window_event(d, ev);

		// Fentre fermee par la croix
		if (ev.type == SDL_QUIT)
			continu = false;
		
	}
	return continu;
}