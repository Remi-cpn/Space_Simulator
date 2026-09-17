/* ************************************************************************** */
/*   Space_Simulator — physics.h                                              */
/*   Newtonian N-body physics : per-object state (Verlet-style position       */
/*   integration) and gravitational acceleration between suns/objects.        */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <math.h>

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../../library/librt/librt.h"

/* ——— Units ———————————————————————————————————————————————————————————————— */
// Distance : 1 unit = 1 AU (Astronomical Unit) = 1.496e11 m
// Mass : 1 unit = 1 solar mass  = 1.989e30 kg
// Times : 1 unit = 1 day = 86400 s

/* ——— Forward Declare —————————————————————————————————————————————————————— */
typedef struct s_data	t_data;
typedef struct s_object	t_object;
typedef struct s_simulation	t_simulation;

/* ——— Define ——————————————————————————————————————————————————————————————— */
# define SOLAR_MASS 1.989e30
# define G_CONST 2.959122e8
# define DT 0.01

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_physics
{
	t_point		cur_pos;
	t_point		prev_pos;
	double		mass;
	t_vec		acc;
}	t_physics;

/* ——— Functions prototypes ————————————————————————————————————————————————— */
void	recalcul_physics(t_data *d, t_simulation *sim);
void	recalcul_pos_obj(t_simulation *sim, int i);
void	calc_acc_obj(t_simulation *sim, int i);
void	calc_acc_sun(t_simulation *sim, int i);

#endif