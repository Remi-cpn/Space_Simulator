/* ************************************************************************** */
/*   Space_Simulator — data.h                                                 */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H


/* ——— Lib Extern ——————————————————————————————————————————————————————————— */



/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../library/librt/librt.h"
# include "data.h"



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
	int		cam_target;
}	t_camera;

typedef struct	s_sphere
{

}	t_sphere;

typedef struct	s_skybox
{
	GLuint	tex;
}	t_skybox;

typedef struct s_object
{
	t_obj				type;
	bool				physics_enabled;
	union u_shape
	{
	//	t_sphere		sphere;
	//	t_cone			cone;
	//	t_plane			plane;
	//	t_cylinder		cylinder;
	//	t_ring			ring;
	}	shape;
}	t_object;

/* ——— World ———————————————————————————————————————————————————————————————— */
typedef struct	s_world
{
	t_camera	cam;
	t_object	*objs;
	t_skybox	sky;
	int			nb_obj;

}	t_world;


/* ——— Function prototypes —————————————————————————————————————————————————— */


#endif