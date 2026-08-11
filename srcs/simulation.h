/* ************************************************************************** */
/*   Space_Simulator — data.h                                                 */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H


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

typedef struct	s_skybox
{

}	t_skybox;


/* ——— World ———————————————————————————————————————————————————————————————— */
typedef struct	s_world
{

}	t_world;


/* ——— Function prototypes —————————————————————————————————————————————————— */


#endif