/* ************************************************************************** */
/*   Space_Simulator — input.h                                                */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <stdbool.h>


/* ——— Structs input ———————————————————————————————————————————————————————— */
typedef struct s_input
{
	bool	d;
	bool	a;
	bool	w;
	bool	s;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	ctrl;
	bool	space;
	bool	shift;
}	t_input;

typedef enum e_key
{
	NONE = -1,
	ESC = 41,
	D = 7,
	A = 4,
	W = 26,
	S = 22,
	UP = 82,
	DOWN = 81,
	LEFT = 80,
	RIGHT = 79,
	LCTRL = 224,
	LSHIFT = 225,
	SPACE = 44,
	R = 21,
	PGUP = 75,
	PGDOWN = 78,
	ENTER = 40,
	BACK = 42,
	TAB = 43,
}	t_key;

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
bool	lisen_poll_event(t_data *d);

#endif