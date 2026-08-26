/* ************************************************************************** */
/*   Space_Simulator — simulation.h                                           */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H


/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include "../external/glad/include/glad/gl.h"



/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../library/librt/librt.h"


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
	//t_physics	param;
	double		radius;
	t_color		color;
	double		intensity;
	t_texture	texture;
}	t_sun;

// typedef struct s_plane
// {
// 	t_point		point;
// 	t_vec		normal;
// }	t_plane;

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
	//t_physics	param;
	double		rotation;
	double		rotation_speed;
}	t_sphere;

// typedef struct s_cylinder
// {
// 	t_point	center;
// 	t_vec	axis;
// 	double	radius;
// 	double	height;
// }	t_cylinder;

// typedef struct s_cone
// {
// 	t_point	apex;
// 	t_vec	axis;
// 	double	angle;
// 	double	height;
// }	t_cone;

typedef struct s_object
{
	t_obj				type;
	char				*name;
	t_color				color;
	t_texture			texture;
	bool				physics_enabled;
	union u_shape
	{
		t_sphere		sphere;
	//	t_cone			cone;
	//	t_plane			plane;
	//	t_cylinder		cylinder;
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
	// Soleils
		t_sun		*suns;
		int			nb_sun;
	// Trous noirs
		t_blackhole	*blackholes;
		int			nb_bh;
	// Lumieres
		t_light		*lights;
		int			nb_light;
	// Amibiente light
		t_color		ambient;
		double		ambient_ratio;
	// SkyBox
		t_skybox	sky;
}	t_simulation;


/* ——— Function prototypes —————————————————————————————————————————————————— */
void	calcul_viewport(t_camera *cam, double ratio);
void	update_cam(t_data *d, double speed, double speed_rot);


#endif