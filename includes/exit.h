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
# define ERROR_FILE_SHADER_OPEN -5
# define ERROR_FILE_SHADER_FSTAT -6
# define ERROR_FILE_SHADER_READ -7
# define ERROR_FILE_SHADER_EMPTY -8
# define ERROR_SHADER_COMPILE -9
# define ERROR_SHADER_LINK -10

// Exit messages
# define ERROR_MALLOC_MSG "Failed to allocate memory"
# define ERROR_FILE_SHADER_OPEN_MSG "Unable to open the shader file"
# define ERROR_FILE_SHADER_FSTAT_MSG "Error when using fstat on shader"
# define ERROR_FILE_SHADER_READ_MSG "Invalid read shader file"
# define ERROR_FILE_SHADER_EMPTY_MSG "Empty shader file"
# define ERROR_SHADER_COMPILE_MSG "Invalid shader compilation"
# define ERROR_SHADER_LINK_MSG "Invalid shader link"

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	exit_prog(t_data *data, int exit_code, const char *error_message);

#endif