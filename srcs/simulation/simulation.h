/* ************************************************************************** */
/*   Space_Simulator — simulation.h                                           */
/*   Scene model : camera, objects, suns, black holes, lights, and the        */
/*   t_simulation struct that ties them together.                             */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H


/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include "../../external/glad/include/glad/gl.h"

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../../library/librt/librt.h"

/* ——— DEFINE     ——————————————————————————————————————————————————————————— */
# define RENDER_DIST 5000.0
# define SHADOW_DIST 4000.0


/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;
typedef struct s_texture	t_texture;

/* ——— Struct texture ——————————————————————————————————————————————————————— */
typedef enum e_tex_type
{
	TEX_NONE,
	TEX_CB,
	TEX_IMG,
}	t_tex_type;

typedef struct s_texture
{
	t_tex_type	type;
	char		*path;
	GLuint		id;
	bool		bump_m;
	GLuint		bump_map_id;
}	t_texture;

/* ——— Struct color ——————————————————————————————————————————————————————— */
typedef struct s_color
{
	int	r;
	int	g;
	int b;
	int a;
}	t_color;

/* ——— Lights —————————————————————————————————————————————————————————————— */
typedef struct s_light
{
	char 		*name;
	t_point		position;
	t_color		color;
	double		intensity;
}	t_light;

/* ——— Objects —————————————————————————————————————————————————————————————— */
typedef enum e_obj
{
	OBJ_NONE,
	OBJ_SKYBOX,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_RING,
}	t_obj;

typedef struct s_camera
{
	t_point		origin;
	t_point		corner;
	t_vec		hor;
	t_vec		hor_n;
	t_vec		ver;
	t_vec		ver_n;
	t_vec		dir;
	double		fov;
	double		focal;
}	t_camera;

typedef struct	s_skybox
{
	GLuint	tex;
}	t_skybox;

typedef struct s_blackhole
{
	char	*name;
	float	mass;
	t_vec	pos;
}	t_blackhole;

typedef struct s_sun
{
	char		*name;
	t_vec		pos;
	double		radius;
	t_color		color;
	double		intensity;
	t_texture	texture;
	double		shininess;
}	t_sun;

typedef struct s_ring
{
	t_point		*center;
	t_vec		normal;
	double		inner_rad;
	double		outer_rad;
}	t_ring;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	double		rotation;
	double		rotation_speed;
}	t_sphere;

typedef struct s_object
{
	t_obj				type;
	char				*name;
	t_color				color;
	t_texture			texture;
	bool				physics_enabled;
	double				shininess;
	union u_shape
	{
		t_sphere		sphere;
		t_ring			ring;
	}	shape;
}	t_object;

/* ——— Simulation ——————————————————————————————————————————————————————————— */
typedef struct	s_simulation
{
	// Cam
		t_camera	cam;
	// Objects
		t_object	*objs;
		int			nb_obj;
	// Suns
		t_sun		*suns;
		int			nb_sun;
	// Black holes
		t_blackhole	*blackholes;
		int			nb_bh;
	// Lights
		t_light		*lights;
		int			nb_light;
	// Ambient light
		t_color		ambient;
		double		ambient_ratio;
	// SkyBox
		t_skybox	sky;
	// Settings
		float		shadow_dist;
}	t_simulation;


/* ——— Function prototypes —————————————————————————————————————————————————— */
void	calcul_viewport(t_camera *cam, double ratio);
void	update_cam(t_data *d, double speed, double speed_rot);


#endif