/* ************************************************************************** */
/*   Space_Simulator — init_texture.c                                        */
/* ************************************************************************** */

#include "../data.h"
#include "../exit/exit.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb/stb_image.h"

// Charge une image (stb_image), l'upload en texture GL avec mipmaps,
// et l'ajoute au cache (avec growth par bloc de 16).
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

	// Creation de la texture GL et upload des pixels -- glActiveTexture
	// explicite avant le bind : sinon on herite de l'unite laissee active
	// par le dernier appelant (ex. bind_object_texture), et on peut
	// ecraser silencieusement son binding au lieu de juste creer/uploader.
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &(d->tex[d->tex_count].id));
	glBindTexture(GL_TEXTURE_2D, d->tex[d->tex_count].id);
	glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, w, h);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Filtrage et wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Generation des mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	d->tex_count++;
	return (&(d->tex[d->tex_count - 1].id));
}

// Cherche une texture deja chargee par son chemin dans le cache.
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

// Renvoie l'id GL d'une texture, en la chargeant seulement si elle
// n'est pas deja dans le cache.
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
