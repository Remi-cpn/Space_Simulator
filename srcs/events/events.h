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
	bool	i;
	bool	o;
	bool	ctrl;
	bool	space;
	bool	r;
	bool	n;
	bool	p;
	bool	most;
	bool	less;
}	t_input;

typedef enum e_key
{
	ESC = 41,
	D = 7,
	A = 4,
	W = 26,
	S = 22,
	UP = 82,
	DOWN = 81,
	LEFT = 80,
	RIGHT = 79,
	I = 12,
	O = 18,
	LCTRL = 224,
	SPACE = 44,
	WHEEL_F = 1,
	WHEEL_B = 2,
	_R = 21,
	N = 17,
	P = 19,
	MOST = 87,
	LESS = 86,
	PGUP = 75,
	PGDOWN = 78,
}	t_key;

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
bool	lisen_poll_event(t_data *d);

#endif