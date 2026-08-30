/* ************************************************************************** */
/*   Space_Simulator — gl_debug.c                                             */
/*   OpenGL debug callback : called directly by the driver whenever           */
/*   something goes wrong.                                                    */
/* ************************************************************************** */

#include "debug.h"

/*	Translates the GLenum "source" of an OpenGL debug message into a
	readable string, for display in gl_debug_callback.	*/
static const char	*debug_source(GLenum source)
{
	if (source == GL_DEBUG_SOURCE_API)
		return ("API");
	if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM)
		return ("WINDOW");
	if (source == GL_DEBUG_SOURCE_SHADER_COMPILER)
		return ("SHADER");
	if (source == GL_DEBUG_SOURCE_THIRD_PARTY)
		return ("THIRD_PARTY");
	if (source == GL_DEBUG_SOURCE_APPLICATION)
		return ("APP");
	return ("OTHER");
}

/*	Translates the GLenum "type" of an OpenGL debug message (error,
	deprecation, perf...) into a readable string.	*/
static const char	*debug_type(GLenum type)
{
	if (type == GL_DEBUG_TYPE_ERROR)
		return ("ERROR");
	if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
		return ("DEPRECATED");
	if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
		return ("UNDEFINED");
	if (type == GL_DEBUG_TYPE_PORTABILITY)
		return ("PORTABILITY");
	if (type == GL_DEBUG_TYPE_PERFORMANCE)
		return ("PERF");
	return ("OTHER");
}

/*	Translates the GLenum "severity" of an OpenGL debug message into
	a readable string (HIGH/MEDIUM/LOW/NOTIF).	*/
static const char	*debug_severity(GLenum severity)
{
	if (severity == GL_DEBUG_SEVERITY_HIGH)
		return ("HIGH");
	if (severity == GL_DEBUG_SEVERITY_MEDIUM)
		return ("MEDIUM");
	if (severity == GL_DEBUG_SEVERITY_LOW)
		return ("LOW");
	return ("NOTIF");
}

/*	Assembles the translations above into one "[GL][SRC][TYPE][SEV] msg"
	line written to stderr, ignores plain notifications.	*/
void APIENTRY	gl_debug_callback(GLenum source, GLenum type, GLuint id,
					GLenum severity, GLsizei length,
					const GLchar *message, const void *user_param)
{
	(void)id;
	(void)length;
	(void)user_param;

	// Can be removed to also see notifications
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return ;

	ft_putstr_fd("[GL][", 2);
	ft_putstr_fd((char *)debug_source(source), 2);
	ft_putstr_fd("][", 2);
	ft_putstr_fd((char *)debug_type(type), 2);
	ft_putstr_fd("][", 2);
	ft_putstr_fd((char *)debug_severity(severity), 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
}
