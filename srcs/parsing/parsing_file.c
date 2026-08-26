/* ************************************************************************** */
/*   Space_Simulator — parcing_file.c                                         */
/* ************************************************************************** */

#include "parsing.h"
#include "../exit/exit.h"

static void	pars_line_solar(t_data *d, char *line)
{
	static int	i = 0;
	static int	j = 0;
	char		**line_split;

	line_split = ft_split(line, ' ');
	if (!line_split || !line_split[0])
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	if (!ft_strncmp(line_split[0], "A", 2))
		add_al(d, line_split);
	else if (!ft_strncmp(line_split[0], "C", 2))
		add_cam(d, line_split);
	else if (!ft_strncmp(line_split[0], "so", 3))
		add_so(d, &d->sim.suns[j++], line_split);
	else if (!ft_strncmp(line_split[0], "bh", 3))
		add_bh(d, &d->sim.objs[i++], line_split);
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
}

// static void	pars_line_rt(t_parsing *p, t_world *w, char *line)
// {
// 	static int	i = 0;

// 	p->line_split = ft_split(line, ' ');
// 	if (!p->line_split || !p->line_split[0])
// 		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
// 	if (!ft_strncmp(p->line_split[0], "A", 2))
// 		add_al(p, w, p->line_split);
// 	else if (!ft_strncmp(p->line_split[0], "C", 2))
// 		add_cam(p, w, p->line_split);
// 	else if (!ft_strncmp(p->line_split[0], "L", 2))
// 		add_light(p, w, p->line_split);
// 	else if (!ft_strncmp(p->line_split[0], "sp", 3))
// 		add_sp(p, &w->objects[i++], p->line_split);
// 	else if (!ft_strncmp(p->line_split[0], "pl", 3))
// 		add_pl(p, &w->objects[i++], p->line_split);
// 	else if (!ft_strncmp(p->line_split[0], "cy", 3))
// 		add_cy(p, &w->objects[i++], p->line_split);
// 	else if (!ft_strncmp(p->line_split[0], "co", 3))
// 		add_co(p, &w->objects[i++], p->line_split);
// 	else
// 		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
// 	ft_free_array(p->line_split);
// 	if (i == w->nb_obj)
// 		i = 0;
// 	p->line_split = NULL;
// }

void	pars_line_dispatch(t_data *d, char *line, bool solar)
{
	if (solar == true)
		pars_line_solar(d, line);
	// else
	// 	pars_line_rt(p, w, l);
}

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
