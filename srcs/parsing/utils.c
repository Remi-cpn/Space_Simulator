/* ************************************************************************** */
/*   Space_Simulator — parcing.c                                              */
/* ************************************************************************** */

#include "parsing.h"
#include "../exit/exit.h"
#include "../simulation.h"

// double	get_mass(char *s)
// {
// 	double	mass_kg;

// 	mass_kg = strtod(s, NULL);
// 	return (mass_kg);
// }

t_vec	get_vec(t_data *d, char *s)
{
	t_vec	vec;
	char	**sp;

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
	{
		ft_free_array(sp);
		exit_prog(d, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	}
	if (!double_valid(sp[0]) || !double_valid(sp[1]) || !double_valid(sp[2]))
	{
		ft_free_array(sp);
		exit_prog(d, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	}
	vec_init(&vec, ft_atod(sp[0]), ft_atod(sp[1]), ft_atod(sp[2]));
	ft_free_array(sp);
	return (vec);
}

t_color	get_color(t_data *d, char *s)
{
	t_color	color;
	char	**sp;
	int		v[3];

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3]
		|| (sp[0] && !int_valid(sp[0])) || (sp[1] && !int_valid(sp[1]))
		|| (sp[3] && !int_valid(sp[2])))
	{
		ft_free_array(sp);
		exit_prog(d, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	}
	v[0] = ft_atoi(sp[0]);
	v[1] = ft_atoi(sp[1]);
	v[2] = ft_atoi(sp[2]);
	ft_free_array(sp);
	if (v[0] < 0 || v[0] > 255 || v[1] < 0 || v[1] > 255
		|| v[2] < 0 || v[2] > 255)
		exit_prog(d, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	color.r = v[0];
	color.g = v[1];
	color.b = v[2];
	color.a = 255;
	return (color);
}

// int	count_light(t_parsing *p, char *file_name)
// {
// 	int		fd;
// 	char	*str;
// 	int		count;

// 	count = 0;
// 	fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		exit_prog_pars(p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
// 	str = ft_get_next_line(fd);
// 	while (str)
// 	{
// 		if (str[0] == 'L')
// 			count++;
// 		str = ft_freenull(str);
// 		str = ft_get_next_line(fd);
// 	}
// 	close(fd);
// 	return (count);
// }

int	count_line(t_data *d, char *file_name)
{
	int		fd;
	char	*str;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog(d, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	str = ft_get_next_line(fd);
	while (str)
	{
		count += (str[0] != '\n' && str[0] != '#');
		d->sim.nb_sun += (str[0] == 's' && str[1] == 'o');
		d->sim.nb_bh += (str[0] == 'b' && str[1] == 'h');
		d->sim.nb_light += (str[0] == 'L');
		str = ft_freenull(str);
		str = ft_get_next_line(fd);
	}
	close(fd);
	return (count);
}
