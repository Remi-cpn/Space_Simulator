/* ************************************************************************** */
/*   Space_Simulator — exit.h                                                 */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <unistd.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
#include "../data.h"

/* ——— Define exit messages (negative values is personal error codes) ——————— */
// Exit codes
	# define EXIT_SUCCESS 0
	# define EXIT_ERROR 1
	# define ERROR_MALLOC -1

// Init
	# define ERROR_SDL_INIT -20
	# define ERROR_SDL_WINDOW -21
	# define ERROR_SDL_CONTEXT -22
	# define ERROR_FBO_INIT -23

// Shaders
	# define ERROR_FILE_SHADER_OPEN -30
	# define ERROR_FILE_SHADER_FSTAT -31
	# define ERROR_FILE_SHADER_READ -32
	# define ERROR_FILE_SHADER_EMPTY -33
	# define ERROR_SHADER_COMPILE -34
	# define ERROR_SHADER_LINK -35

// Exit messages
# define ERROR_MALLOC_MSG "Failed to allocate memory"
# define ERROR_FILE_SHADER_OPEN_MSG "Unable to open the shader file"
# define ERROR_FILE_SHADER_FSTAT_MSG "Error when using fstat on shader"
# define ERROR_FILE_SHADER_READ_MSG "Invalid read shader file"
# define ERROR_FILE_SHADER_EMPTY_MSG "Empty shader file"
# define ERROR_SHADER_COMPILE_MSG "Invalid shader compilation"
# define ERROR_SHADER_LINK_MSG "Invalid shader link"
# define ERROR_FBO_INIT_MSG "Failed to init fbo"

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	exit_prog(t_data *data, int exit_code, const char *error_message);

#endif