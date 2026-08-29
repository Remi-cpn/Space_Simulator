/* ************************************************************************** */
/*   Space_Simulator — exit.h                                                 */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <unistd.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../data.h"
# include "../../library/libft/libft.h"

/* ——— Define exit messages (negative values is personal error codes) ——————— */
	# define EXIT_SUCCESS 0
	# define EXIT_ERROR 1
	# define ERROR_MALLOC -1
	# define ERROR_MALLOC_MSG "Failed to allocate memory"

// Init
	# define ERROR_SDL_INIT -20
	# define ERROR_SDL_WINDOW -21
	# define ERROR_SDL_CONTEXT -22
	# define ERROR_FBO_INIT -23
	# define ERROR_TEXTURE_LOAD -24
	# define ERROR_FBO_INIT_MSG "Failed to init fbo"
	# define ERROR_TEXTURE_LOAD_MSG "Failed to init texture"

// Parsing
	# define ERROR_FILE_NAME -30
	# define ERROR_FILE_ARGS -31
	# define ERROR_FILE_CAM -32
	# define ERROR_FILE_LIGHT -33
	# define ERROR_FILE_AL -34
	# define ERROR_FILE_OBJ -35
	# define ERROR_FILE_TEX -36
	# define ERROR_FILE_BUMP -37
	# define ERROR_FILE_NAME_MSG "Incorrect file name"
	# define ERROR_FILE_ARGS_MSG "Incorrect file arguments"
	# define ERROR_FILE_CAM_MSG "Only one camera needs to be defined in the file"
	# define ERROR_FILE_CAM_ARGS_MSG "Camera must be defined with valid arguments"
	# define ERROR_FILE_LIGHT_MSG "Only one light needs to be defined in the file"
	# define ERROR_FILE_LIGHT_ARGS_MSG "Light must be defined with valid arguments"
	# define ERROR_FILE_AL_MSG "Only one ambient light needs to be defined in the file"
	# define ERROR_FILE_AL_ARGS_MSG "Ambient light must be defined with valid arguments"
	# define ERROR_FILE_SP_ARGS_MSG "Sphere must be defined with valid arguments"
	# define ERROR_FILE_BH_ARGS_MSG "BlackHole must be defined with valid arguments"
	# define ERROR_FILE_SO_ARGS_MSG "Solars must be defined with valid arguments"
	# define ERROR_FILE_PL_ARGS_MSG "Plane must be defined with valid arguments"
	# define ERROR_FILE_CY_ARGS_MSG "Cylinder must be defined with valid arguments"
	# define ERROR_FILE_CO_ARGS_MSG "Cone must be defined with valid arguments"
	# define ERROR_FILE_RI_ARGS_MSG "Ring must be defined with valid arguments"
	# define ERROR_FILE_TEX_MSG "Incorrect file texture name"
	# define ERROR_FILE_BUMP_MSG "Incorrect file bump_map name"

// Shaders
	# define ERROR_FILE_SHADER_OPEN -40
	# define ERROR_FILE_SHADER_FSTAT -41
	# define ERROR_FILE_SHADER_READ -42
	# define ERROR_FILE_SHADER_EMPTY -43
	# define ERROR_SHADER_COMPILE -44
	# define ERROR_SHADER_LINK -45
	# define ERROR_TEX_LIMIT -46
	# define ERROR_FILE_SHADER_OPEN_MSG "Unable to open the shader file"
	# define ERROR_FILE_SHADER_FSTAT_MSG "Error when using fstat on shader"
	# define ERROR_FILE_SHADER_READ_MSG "Invalid read shader file"
	# define ERROR_FILE_SHADER_EMPTY_MSG "Empty shader file"
	# define ERROR_SHADER_COMPILE_MSG "Invalid shader compilation"
	# define ERROR_SHADER_LINK_MSG "Invalid shader link"
	# define ERROR_TEX_LIMIT_MSG "Too many object textures for the GPU texture-unit budget"


/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	exit_prog(t_data *data, int exit_code, const char *error_message);

#endif