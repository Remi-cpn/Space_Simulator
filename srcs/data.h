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
# include "parsing/parsing.h"


/* ——— Define ——————————————————————————————————————————————————————————————— */
# define WIN_W 1280
# define WIN_H 720
# define WIN_ID 0


/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_input	t_input;
typedef struct s_hud_db	t_hud_db;


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
	// Simulation
		t_simulation	sim;
	// Objets GPU
		GLuint			sphere_ssbo;
		GLuint			ring_ssbo;
		GLuint			light_ssbo;
		GLuint			blackhole_ssbo;
	// Reglage
		t_input			input;
		unsigned int	nbr_ray;
		unsigned int	wheel_coef;
		float			exposure;
		float			gamma;
		bool			ss_file;
	// Camera
		int				cam_target;
	// HUD
		t_hud_db		*hud_db;
}	t_data;


/* ——— Function prototypes —————————————————————————————————————————————————— */
// Fonctions d'initialisation
t_data			init_program(void);
void			init_image(t_data *d);
void			init_resize_image(t_data *d, int new_w, int new_h);
GLuint			load_texture(t_data *d, char *path);
void			init_hud(t_data *d);

#endif