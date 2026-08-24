/* ************************************************************************** */
/*   Space_Simulator — gl_debug.c                                             */
/*   Callback de debug OpenGL : le driver l'appelle seul en cas de problème.  */
/* ************************************************************************** */

#include "debug.h"

#ifndef APIENTRY
# define APIENTRY
#endif

// Traduit le GLenum "source" d'un message de debug OpenGL en chaine
// lisible, pour l'affichage dans gl_debug_callback.
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

// Traduit le GLenum "type" d'un message de debug OpenGL (erreur,
// deprecation, perf...) en chaine lisible.
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

// Traduit le GLenum "severity" d'un message de debug OpenGL en
// chaine lisible (HIGH/MEDIUM/LOW/NOTIF).
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

// Assemble les traductions ci-dessus en une ligne "[GL][SRC][TYPE][SEV] msg"
// ecrite sur stderr ; ignore les simples notifications.
void APIENTRY	gl_debug_callback(GLenum source, GLenum type, GLuint id,
					GLenum severity, GLsizei length,
					const GLchar *message, const void *user_param)
{
	(void)id;
	(void)length;
	(void)user_param;

	// Peut etre supprimé pour voir les notifications
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
