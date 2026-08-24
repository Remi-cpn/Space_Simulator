/* ************************************************************************** */
/*   Space_Simulator — data.h                                                 */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H



/* ——— Lib Extern ——————————————————————————————————————————————————————————— */


/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
# include "../external/glad/include/glad/gl.h"
# include <SDL2/SDL.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "events/events.h"
# include "../library/libft/libft.h"
# include "simulation.h"


/* ——— Define ——————————————————————————————————————————————————————————————— */
# define WIN_W 1280
# define WIN_H 720
# define WIN_ID 0


/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_input	t_input;


/* ——— Struct texture ——————————————————————————————————————————————————————— */
typedef struct s_texture
{
	char	*path;
	GLuint	id;
}	t_texture;


/* ——— Struct data —————————————————————————————————————————————————————————— */
typedef struct s_data
{
	// Window
		SDL_Window		*win;
		int				win_h;
		int				win_w;
		SDL_GLContext	ctx;

	GLuint			img;
	GLuint			fbo;
	GLuint			program;

	// Textures
		t_texture		*tex;
		int				tex_count;
		int				tex_capacity;

	t_input			input;
	t_simulation	sim;
	unsigned int	nbr_ray;

	// Camera
	int				cam_target;
}	t_data;


/* ——— Function prototypes —————————————————————————————————————————————————— */
// Fonctions d'initialisation
t_data			init_program(void);
void			init_image(t_data *d);
void			init_resize_image(t_data *d, int new_w, int new_h);
GLuint			load_texture(t_data *d, char *path);

#endif