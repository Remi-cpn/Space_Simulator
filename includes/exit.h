/* ************************************************************************** */
/*   Space_Simulator — exit.h                                                 */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <unistd.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
#include "data.h"

/* ——— Define exit messages (negative values is personal error codes) ——————— */
// Exit codes
# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define ERROR_MALLOC -1
# define ERROR_SDL_INIT -2
# define ERROR_SDL_WINDOW -3
# define ERROR_SDL_CONTEXT -4

// Exit messages
# define ERROR_MALLOC_MSG "Failed to allocate memory"

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	exit_prog(t_data *data, int exit_code, const char *error_message);

#endif