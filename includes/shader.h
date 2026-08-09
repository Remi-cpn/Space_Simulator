/* ************************************************************************** */
/*   Space_Simulator — shader.h                                               */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H


/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <fcntl.h>
#include <sys/stat.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
#include "includes/data.h"


/* ——— Function prototypes —————————————————————————————————————————————————— */
char	*read_source_compute_shader(t_data *d, char *shader_name);
//GLuint create_shader_program(const char *vertex_path, const char *fragment_path);

#endif