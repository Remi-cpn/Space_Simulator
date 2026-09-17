/* ************************************************************************** */
/*   Space_Simulator — routine.c                                              */
/*   Worker thread loop : pulls job indices from the pool and dispatches      */
/*   them to the right physics function.                                      */
/* ************************************************************************** */

#include "../data.h"
#include "../physics/physics.h"

/*	Redirects the job to the right physics function based on the
	pool's current mode.	*/
static void	dispatch_work(t_data *d, int idx)
{
	if (d->pool.mod == PHYS_ACC)
		calc_acc_obj(&d->sim, idx);
	else if (d->pool.mod == PHYS_SUN)
		calc_acc_sun(&d->sim, idx);
	else
		recalcul_pos_obj(&d->sim, idx);
}

/*	A worker thread's loop : waits for a job, runs it, signals
	completion via the semaphore, until the pool stops.	*/
void	*routine(void *params)
{
	t_data	*d;
	int		idx;

	d = (t_data *)params;
	pthread_mutex_lock(&d->pool.queue);
	while (d->pool.stop == false)
	{
		while ((!d->pool.start
				|| d->pool.job_idx >= d->pool.nbr_jobs)
			&& !d->pool.stop)
			pthread_cond_wait(&d->pool.cond, &d->pool.queue);
		if (d->pool.stop)
			break ;
		idx = d->pool.job_idx;
		d->pool.job_idx++;
		pthread_mutex_unlock(&d->pool.queue);
		dispatch_work(d, idx);
		sem_post(&d->pool.sem);
		pthread_mutex_lock(&d->pool.queue);
	}
	pthread_mutex_unlock(&d->pool.queue);
	return (NULL);
}
