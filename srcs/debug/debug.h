/* ************************************************************************** */
/*   Space_Simulator — debug.h                                                */
/*   Debug tooling : the OpenGL debug callback (gl_debug.c) and the           */
/*   navigable HUD tree (hud.c / hud_db.c / init_hud.c).                      */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include "../../external/glad/include/glad/gl.h"
# include <SDL2/SDL.h>

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../../library/libft/libft.h"
# include "../data.h"

/* ——— Define ——————————————————————————————————————————————————————————————— */
# define YELLOW_BOLD "\033[1;33m"
# define HIGHLIGHT   "\033[7m"
# define RESET       "\033[0m"

// APIENTRY is defined here for portability.
#ifndef APIENTRY
# define APIENTRY
#endif

/* ——— Struct HUD ——————————————————————————————————————————————————————————— */
typedef enum s_tag
{
	HUD_NONE,
	HUD_UINT,
	HUD_INT,
	HUD_FLOAT,
	HUD_DOUBLE,
}	t_tag;

typedef struct s_hud_db
{
	char		*name;
	t_tag		tag;
	union u_value_ptr
	{
		unsigned int	*u;
		int				*i;
		float			*f;
		double			*d;
	}	u_value_ptr;
	t_hud_db	*parent;
	t_hud_db	*head;
	t_hud_db	*child;
	t_hud_db	*next;
}	t_hud_db;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void APIENTRY	gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user_param);
void			print_hud(t_data *d, t_hud_db *target);
t_hud_db		*hud_new(t_data *d, char *name, t_tag tag, void *ptr);
void			hud_append(t_hud_db *parent, t_hud_db **head, t_hud_db *new_node);
t_hud_db		*hud_select(t_data *d, t_key key);

#endif
