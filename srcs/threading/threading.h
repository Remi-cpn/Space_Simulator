/* ************************************************************************** */
/*   Space_Simulator — threading.h                                            */
/*   Worker thread pool : job modes, sync primitives, shared state            */
/*   between recalcul_physics and the worker loop.                            */
/* ************************************************************************** */

#ifndef THREADING_H
# define THREADING_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <sys/sysinfo.h>
# include <semaphore.h>
# include <pthread.h>

/* ——— DEFINE ——————————————————————————————————————————————————————————————— */
# define TILE_SIZE 128

/* ——— Forward Declare —————————————————————————————————————————————————————— */
typedef struct s_simulation	t_simulation;
typedef struct s_data			t_data;
typedef struct s_object		t_object;

/* ——— Multi Threading —————————————————————————————————————————————————————— */
typedef enum e_mod
{
	PHYS_ACC,
	PHYS_SUN,
	PHYS_POS,
	RENDER
}	t_mod;

typedef struct s_threading
{
	t_mod			mod;
	int				nbr_threads;
	pthread_t		*threads;
	pthread_mutex_t	queue;
	bool			mutex_ready;
	pthread_cond_t	cond;
	bool			cond_ready;
	sem_t			sem;
	bool			sem_ready;
	bool			start;
	bool			stop;
	int				job_idx;
	int				nbr_jobs;
	int				nbr_tiles;
}	t_threading;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	init_threads(t_data *d);
void	*routine(void *params);


#endif