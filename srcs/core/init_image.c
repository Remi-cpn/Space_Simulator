/* ************************************************************************** */
/*   Space_Simulator — init_image.c                                           */
/*   Creates and resizes the compute shader's output texture and its FBO.     */
/* ************************************************************************** */

#include "../data.h"
#include "../exit/exit.h"
#include "../debug/debug.h"

/*	Recreates the texture/FBO at the new window size.	*/
void	init_resize_image(t_data *d, int new_w, int new_h)
{
	if (d->fbo)
		glDeleteFramebuffers(1, &(d->fbo));
	if (d->img)
		glDeleteTextures(1, &(d->img));
	d->win_w = new_w;
	d->win_h = new_h;
	if (d->win_w < 1)
		d->win_w = 1;
	if (d->win_h < 1)
		d->win_h = 1;
	init_image(d);
}

/*	Creates the compute shader's output texture and the FBO that lets
	it be blitted to the screen afterwards.	*/
void	init_image(t_data *d)
{
	glGenTextures(1, &(d->img));
	glBindTexture(GL_TEXTURE_2D, d->img);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, d->win_w, d->win_h);
	glBindImageTexture(0, d->img, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	glGenFramebuffers(1, &(d->fbo));
	glBindFramebuffer(GL_FRAMEBUFFER, d->fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, d->img, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		exit_prog(d, ERROR_FBO_INIT, ERROR_FBO_INIT_MSG);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
