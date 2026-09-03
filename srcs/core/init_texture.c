/* ************************************************************************** */
/*   Space_Simulator — init_texture.c                                         */
/*   GL texture cache : loads images via stb_image and reuses already         */
/*   loaded ones by path.                                                     */
/* ************************************************************************** */

#include "../data.h"
#include "../exit/exit.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb/stb_image.h"

/*	Loads an image (stb_image), uploads it as a GL texture with
	mipmaps, and adds it to the cache (growing by blocks of 16).	*/
static GLuint	*add_texture(t_data *d, char *path)
{
	int				w;
	int				h;
	int				channels;
	unsigned char	*data;
	GLsizei			levels;

	if (d->tex_count >= d->tex_capacity)
	{
		d->tex_capacity += 16;
		d->tex = ft_realloc(d->tex, d->tex_capacity - 16, d->tex_capacity, sizeof(t_texture));
		if (!d->tex)
		{
			d->tex_count = 0;
			exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
		}
	}
	d->tex[d->tex_count].path = ft_strdup(path, 0);
	if (!d->tex[d->tex_count].path)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);

	data = stbi_load(path, &w, &h, &channels, 4);
	if (!data)
		exit_prog(d, ERROR_TEXTURE_LOAD, ERROR_TEXTURE_LOAD_MSG);

	levels = (GLsizei)(floor(log2(fmax(w, h))) + 1);

	// Creates the GL texture and uploads the pixels. Explicit glActiveTexture
	// before the bind, otherwise we inherit whichever unit was left active
	// by the last caller.
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &(d->tex[d->tex_count].id));
	glBindTexture(GL_TEXTURE_2D, d->tex[d->tex_count].id);
	glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, w, h);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Filtering and wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Mipmap generation
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	d->tex_count++;
	return (&(d->tex[d->tex_count - 1].id));
}

/*	Looks for a texture already loaded, by its path, in the cache.	*/
static t_texture *find_texture(t_data *d, char *path)
{
	int	i;

	i = 0;
	while (i < d->tex_count)
	{
		if (ft_strncmp(path, d->tex[i].path, ft_strlen(path) + 1) == 0)
			return (&(d->tex[i]));
		i++;
	}
	return (NULL);
}

/*	Returns a texture's GL id, loading it only if it isn't already
	in the cache.	*/
GLuint	load_texture(t_data *d, char *path)
{
	t_texture	*t;
	GLuint		*id;

	if (!path || !path[0])
		return (0);
	t = find_texture(d, path);
	if (t)
		return (t->id);
	id = add_texture(d, path);
	return (*id);
}
