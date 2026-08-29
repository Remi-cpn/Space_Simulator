/* ************************************************************************** */
/*   Space_Simulator — shader.h                                               */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H


/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <fcntl.h>
#include <sys/stat.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
#include "../data.h"

// Doit correspondre a obj_textures[N] dans shader.comp -- aucun mecanisme
// de partage C/GLSL dans ce projet, a garder synchronise a la main.
# define OBJ_TEXTURES_MAX 16

/* ——— Struct GPU ——————————————————————————————————————————————————————————— */
typedef struct s_gpu_light
{
	float	center[3];
	float	intensity;
	float	color[4];
}	t_gpu_light;

typedef struct s_gpu_sphere
{
	float	center[3];
	float	radius;
	float	color[4];
	int		emissive;
	float	intensity;
	int		tex_index;
	float	pad0;
}	t_gpu_sphere;

typedef struct s_gpu_ring
{
	float	center[3];
	float	inner_rad;
	float	normal[3];
	float	outer_rad;
	float	color[4];
	int		tex_index;
	float	pad0;
	float	pad1;
	float	pad2;
}	t_gpu_ring;

typedef struct s_gpu_blackhole
{
	float	center[3];
	float	mass;
}	t_gpu_blackhole;


/* ——— Function prototypes —————————————————————————————————————————————————— */
char	*read_source_compute_shader(t_data *d, char *shader_name);
GLuint	create_compute_shader(t_data *d, char *shader_name);
void	params_gl(t_data *d);
void	init_object_buffers(t_data *d);
void	upload_sphere_buffer(t_data *d);
void	upload_ring_buffer(t_data *d);
void	upload_light_buffer(t_data *d);
void	upload_blackhole_buffer(t_data *d);
void	init_obj_texture_units(t_data *d);

#endif