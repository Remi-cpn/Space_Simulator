/* ************************************************************************** */
/*   Space_Simulator — build_buffer.c                                         */
/* ************************************************************************** */

#include "shader.h"
#include "../exit/exit.h"

// Un soleil est une sphere emissive : on le range dans le meme buffer
// que les spheres classiques (emissive = 1), a la suite. Les vraies
// spheres sont remplies en premier (emissive = 0, deja zero via
// ft_calloc), puis les soleils.
void	upload_sphere_buffer(t_data *d)
{
	t_gpu_sphere	*spheres;
	int				nb_sphere;
	int				total;
	int				i;
	int				j;

	nb_sphere = 0;
	i = 0;
	while (i < d->sim.nb_obj)
	{
		nb_sphere += (d->sim.objs[i].type == OBJ_SPHERE);
		i++;
	}
	total = nb_sphere + d->sim.nb_sun;
	spheres = ft_calloc(total, sizeof(t_gpu_sphere));
	if (!spheres)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	i = 0;
	j = 0;
	while (i < d->sim.nb_obj)
	{
		if (d->sim.objs[i].type == OBJ_SPHERE)
		{
			spheres[j].center[0] = d->sim.objs[i].shape.sphere.center.x;
			spheres[j].center[1] = d->sim.objs[i].shape.sphere.center.y;
			spheres[j].center[2] = d->sim.objs[i].shape.sphere.center.z;
			spheres[j].radius = (float)d->sim.objs[i].shape.sphere.radius;
			spheres[j].color[0] = d->sim.objs[i].color.r / 255.0f;
			spheres[j].color[1] = d->sim.objs[i].color.g / 255.0f;
			spheres[j].color[2] = d->sim.objs[i].color.b / 255.0f;
			spheres[j].color[3] = 1.0f;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < d->sim.nb_sun)
	{
		spheres[j].center[0] = d->sim.suns[i].pos.x;
		spheres[j].center[1] = d->sim.suns[i].pos.y;
		spheres[j].center[2] = d->sim.suns[i].pos.z;
		spheres[j].radius = (float)d->sim.suns[i].radius;
		spheres[j].color[0] = d->sim.suns[i].color.r / 255.0f;
		spheres[j].color[1] = d->sim.suns[i].color.g / 255.0f;
		spheres[j].color[2] = d->sim.suns[i].color.b / 255.0f;
		spheres[j].color[3] = 1.0f;
		spheres[j].emissive = 1;
		i++;
		j++;
	}
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, d->sphere_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, total * sizeof(t_gpu_sphere),
		spheres, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, d->sphere_ssbo);
	free(spheres);
}

// shape.ring.center est un pointeur (aliase le centre de sa sphere
// parente, voir add_ri) -> il faut le dereferencer avant l'upload, le
// buffer GPU ne peut pas stocker de pointeur.
void	upload_ring_buffer(t_data *d)
{
	t_gpu_ring	*rings;
	t_point		*center;
	int			nb_ring;
	int			i;
	int			j;

	nb_ring = 0;
	i = 0;
	while (i < d->sim.nb_obj)
	{
		nb_ring += (d->sim.objs[i].type == OBJ_RING);
		i++;
	}
	rings = ft_calloc(nb_ring, sizeof(t_gpu_ring));
	if (!rings)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	i = 0;
	j = 0;
	while (i < d->sim.nb_obj)
	{
		if (d->sim.objs[i].type == OBJ_RING)
		{
			center = d->sim.objs[i].shape.ring.center;
			rings[j].center[0] = center->x;
			rings[j].center[1] = center->y;
			rings[j].center[2] = center->z;
			rings[j].inner_rad = (float)d->sim.objs[i].shape.ring.inner_rad;
			rings[j].normal[0] = d->sim.objs[i].shape.ring.normal.x;
			rings[j].normal[1] = d->sim.objs[i].shape.ring.normal.y;
			rings[j].normal[2] = d->sim.objs[i].shape.ring.normal.z;
			rings[j].outer_rad = (float)d->sim.objs[i].shape.ring.outer_rad;
			rings[j].color[0] = d->sim.objs[i].color.r / 255.0f;
			rings[j].color[1] = d->sim.objs[i].color.g / 255.0f;
			rings[j].color[2] = d->sim.objs[i].color.b / 255.0f;
			rings[j].color[3] = 1.0f;
			j++;
		}
		i++;
	}
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, d->ring_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, nb_ring * sizeof(t_gpu_ring),
		rings, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, d->ring_ssbo);
	free(rings);
}
