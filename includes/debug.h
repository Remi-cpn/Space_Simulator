/* ************************************************************************** */
/*   Space_Simulator — debug.h                                                */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H


#include "../external/glad/include/glad/gl.h"
#include <SDL2/SDL.h>

#include "../library/libft/libft.h"

#ifndef APIENTRY
# define APIENTRY
#endif

/* ——— Function prototypes —————————————————————————————————————————————————— */
void			print_error(const char *message);
// APIENTRY est la pour la portabilité
void APIENTRY	gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user_param);



#endif