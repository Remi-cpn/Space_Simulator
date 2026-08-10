/* ************************************************************************** */
/*   Space_Simulator — data.h                                                 */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H



/* ——— Lib Extern ——————————————————————————————————————————————————————————— */


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
#include "events.h"
#include "../library/libft/libft.h"

/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
#include "../external/glad/include/glad/gl.h"
#include <SDL2/SDL.h>


/* ——— Define ——————————————————————————————————————————————————————————————— */
#define WIN_W 1280
#define WIN_H 720
#define WIN_ID 0


/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_input	t_input;


/* ——— Structs data ————————————————————————————————————————————————————————— */
typedef struct s_data
{
	SDL_Window		*win;
	int				win_h;
	int				win_w;
	SDL_GLContext	ctx;
	GLuint			img;
	GLuint			fbo;
	GLuint			program;
	t_input			input;
	int				cam_target;
}	t_data;


/* ——— Function prototypes —————————————————————————————————————————————————— */
// Fonctions d'initialisation
t_data	init_program(void);
void	init_image(t_data *d);
void	init_resize_image(t_data *d, int new_w, int new_h);

#endif