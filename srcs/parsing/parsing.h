/* ************************************************************************** */
/*   Space_Simulator — parcing.h                                              */
/* ************************************************************************** */

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <fcntl.h>
# include <stdbool.h>


/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../simulation.h"
# include "../data.h"
# include "../exit/exit.h" 



/* ——— Forward declare —————————————————————————————————————————————————— */
typedef struct s_data		t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	parsing(t_data *d, char *file_name);
void	init_sim(t_data *d);

void	add_cam(t_simulation *s, char **line_split);