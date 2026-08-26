/* ************************************************************************** */
/*   Space_Simulator — parcing.h                                              */
/* ************************************************************************** */

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <fcntl.h>
# include <stdbool.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../simulation.h"
# include "../data.h"
# include "../../library/librt/librt.h"



/* ——— Forward declare —————————————————————————————————————————————————————— */
typedef struct s_data		t_data;
typedef struct s_vec		t_vec;

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
// typedef enum e_type
// {
// 	INT,
// 	LONG,
// 	FLOAT,
// 	DOUBLE
// }	t_type;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	parsing(t_data *d, char *file_name);
void	pars_file(t_data *d, char *file_name, bool solar);
void	pars_texture_map(t_data *d, t_texture *t, char *texture_file, char *bump_file);
void	init_sim(t_data *d);
void	init_hud(t_data *d);

void	add_cam(t_simulation *s, char **line_split);
void	add_bh(t_data *d, t_object *o, char **l_split);
void	add_sp_solar(t_data *d, t_object *o, char **l_split);
void	add_ri(t_data *d, t_object *o, char **l_split, int idx);
void	add_so(t_data *d, t_sun *s, char **l);
void	add_light(t_data *d, char **line_split);
void	add_al(t_data *d, char **line_split);

int		count_line(t_data *d, char *file_name);
t_vec	get_vec(t_data *d, char *s);
t_color	get_color(t_data *d, char *s);