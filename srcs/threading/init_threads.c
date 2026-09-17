/* ************************************************************************** */
/*   Space_Simulator — init_threads.c                                         */
/*   Sets up the worker thread pool : sync primitives, thread creation,       */
/*   tile count for the future render mode.                                   */
/* ************************************************************************** */

#include "../data.h"
#include "../exit/exit.h"

/*	Initializes the thread pool (mutex/cond/sem, thread creation) and
	precomputes the tile count for the future RENDER mode.	*/
void	init_threads(t_data *d)
{
	int	i;

	ft_memset(&d->pool, 0, sizeof(t_threading));
	d->pool.nbr_threads = get_nprocs();
	d->pool.threads = ft_calloc(d->pool.nbr_threads, sizeof(pthread_t));
	if (!d->pool.threads)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	if (pthread_mutex_init(&(d->pool.queue), NULL) != 0)
		exit_prog(d, ERROR_MUTEX, ERROR_MUTEX_MSG);
	d->pool.mutex_ready = true;
	if (pthread_cond_init(&d->pool.cond, NULL) != 0)
		exit_prog(d, ERROR_THREAD, ERROR_THREAD_MSG);
	d->pool.cond_ready = true;
	if (sem_init(&d->pool.sem, 0, 0) == -1)
		exit_prog(d, ERROR_THREAD, ERROR_THREAD_MSG);
	d->pool.sem_ready = true;
	i = -1;
	while (++i < d->pool.nbr_threads)
	{
		if (pthread_create(&(d->pool.threads[i]), NULL, routine, d) != 0)
			exit_prog(d, ERROR_THREAD, ERROR_THREAD_MSG);
	}
	d->pool.nbr_tiles = ((d->win_w + TILE_SIZE - 1) / TILE_SIZE)
		* ((d->win_h + TILE_SIZE - 1) / TILE_SIZE);
}
