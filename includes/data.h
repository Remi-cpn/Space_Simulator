/* ************************************************************************** */
/*   Space_Simulator — data.h                                                 */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H



/* ——— Lib Extern ——————————————————————————————————————————————————————————— */


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
#include "includes/input.h"
#include "../library/libft/libft.h"

/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


/* ——— Define ——————————————————————————————————————————————————————————————— */
#define WIN_W 1280
#define WIN_H 720


/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_input	t_input;


/* ——— Structs data ————————————————————————————————————————————————————————— */
typedef struct s_data
{
	SDL_Window		*win;
	SDL_GLContext	*ctx;
	t_input			input;
	int				cam_target;
}	t_data;


/* ——— Function prototypes —————————————————————————————————————————————————— */
// Fonctions d'initialisation
t_data	init_program(void);

#endif