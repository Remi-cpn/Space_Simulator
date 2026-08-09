/* ************************************************************************** */
/*   Space_Simulator — shader.c                                               */
/* ************************************************************************** */

#include "includes/shader.h"
#include "includes/exit.h"

char	*read_source_compute_shader(t_data *d, char *shader_name)
{
	int			fd;
	int			res;
	int			total_read;
	struct stat	st;
	char		*buffer;
	
	fd = open(shader_name, O_RDONLY);
	if (fd == -1)
		exit_prog(d, ERROR_FILE_SHADER_OPEN, ERROR_FILE_SHADER_OPEN_MSG);
	if (fstat(fd, &st) == -1)
	{
		close(fd);
		exit_prog(d, ERROR_FILE_SHADER_FSTAT, ERROR_FILE_SHADER_FSTAT_MSG);
	}

	buffer = ft_calloc(st.st_size + 1, sizeof(char));
	if (!buffer)
	{
		close(fd);
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	}

	total_read = 0;
	res = 0;
	while (st.st_size > total_read)
	{
		res = read(fd, buffer + total_read, st.st_size - total_read);
		if (res == -1)
		{
			free(buffer);
			close(fd);
			exit_prog(d, ERROR_FILE_SHADER_READ, ERROR_FILE_SHADER_READ_MSG);
		}
		if (res == 0)
			break;
		total_read += res;
	}

	close(fd);
	return (buffer);
}
