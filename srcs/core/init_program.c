/* ************************************************************************** */
/*   Space_Simulator — init_program.c                                         */
/*   Global bootstrap : SDL/GL context, glad, debug callback, output          */
/*   texture, shader compilation, default runtime state.                      */
/* ************************************************************************** */

#include "../data.h"
#include "../exit/exit.h"
#include "../debug/debug.h"
#include "../shaders/shader.h"

// Returns a t_input entirely at zero (no key pressed).
static t_input	init_input(void)
{
	t_input	i;

	ft_memset(&i, 0, sizeof(t_input));
	return (i);
}

// Initializes SDL, creates the window and the OpenGL 4.3 Core context,
// with the debug flag to retrieve driver errors.
static void	init_SDL(t_data *d)
{
	// Video system initialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_prog(d, ERROR_SDL_INIT, SDL_GetError());

	// SDL version choice
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Profile choice
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	// For off-screen rendering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// For shader compilation errors
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	// Window initialization
	d->win = SDL_CreateWindow("Space_Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, d->win_w, d->win_h, SDL_WINDOW_OPENGL);
	if (!d->win)
		exit_prog(d, ERROR_SDL_WINDOW, SDL_GetError());

	// Context initialization, the complete OpenGL state
	d->ctx = SDL_GL_CreateContext(d->win);
	if (!d->ctx)
		exit_prog(d, ERROR_SDL_CONTEXT, SDL_GetError());
}

// Entry point for the global init : SDL/GL, glad, debug callback,
// output texture, shader compilation, default state.
t_data	init_program(void)
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	d.win_w = WIN_W;
	d.win_h = WIN_H;
	init_SDL(&d);

	// Loading glad, which gives access to modern OpenGL functions
	gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

	// Debug system setup
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(gl_debug_callback, NULL);

	init_image(&d);

	// Init the shader's object structures
	init_object_buffers(&d);

	// Shader creation
	d.program = create_compute_shader(&d, "srcs/shaders/shader.comp");
	init_obj_texture_units(&d);

	// Settings
	d.input = init_input();
	d.nbr_ray = 2;
	d.wheel_coef = 1;
	d.exposure = 1.0;
	d.gamma = 1.0;
	d.steps = 500;
	d.step_size = 1.0;
	return (d);
}
