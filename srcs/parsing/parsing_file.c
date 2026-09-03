/* ************************************************************************** */
/*   Space_Simulator — parsing_file.c                                         */
/*   Reads a scene file line by line and dispatches each line to the          */
/*   right parsing function.                                                  */
/* ************************************************************************** */

#include "parsing.h"
#include "../exit/exit.h"

/*	Dispatches to the parsing function based on the identifier found
	at the start of the line.	*/
static void	pars_line_ss(t_data *d, char *line)
{
	static int	i = 0;
	static int	j = 0;
	static int	k = 0;
	char		**line_split;

	line_split = ft_split(line, ' ');
	if (!line_split || !line_split[0])
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	if (!ft_strncmp(line_split[0], "A", 2))
		add_al(d, line_split);
	else if (!ft_strncmp(line_split[0], "C", 2))
		add_cam(d, line_split);
	else if (!ft_strncmp(line_split[0], "L", 2))
 		add_light(d, line_split);
	else if (!ft_strncmp(line_split[0], "so", 3))
		add_so(d, &d->sim.suns[j++], line_split);
	else if (!ft_strncmp(line_split[0], "bh", 3))
		add_bh(d, &d->sim.blackholes[k++], line_split);
	else if (!ft_strncmp(line_split[0], "sp", 3))
		add_sp_solar(d, &d->sim.objs[i++], line_split);
	else if (!ft_strncmp(line_split[0], "ri", 3))
	{
		add_ri(d, &d->sim.objs[i], line_split, i);
		i++;
	}
	else
		exit_prog(d, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	ft_free_array(line_split);
	i = (i != d->sim.nb_obj) * i;
	j = (j != d->sim.nb_sun) * j;
	k = (k != d->sim.nb_bh) * k;
}

/*	To handle several file types.	*/
void	pars_line_dispatch(t_data *d, char *line, bool solar)
{
	if (solar == true)
		pars_line_ss(d, line);
}

/*	Opens the file given as parameter and extracts its lines one by
	one to send them for parsing.	*/
void	pars_file(t_data *d, char *file_name, bool solar)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog(d, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	line = ft_get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && line[0] != '#')
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			pars_line_dispatch(d, line, solar);
		}
		line = ft_freenull(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}
