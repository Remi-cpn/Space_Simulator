/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:07:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 16:28:47 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRT_H
# define LIBRT_H

# include "math.h"
# include "../libft/libft.h"

# define P_INT_MAX "2147483647"
# define P_INT_MIN "2147483648"
# define P_LONG_MAX "9223372036854775807"
# define P_LONG_MIN "9223372036854775808"
# define PI 3.14159265358979323846
# define EPS 0.001

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_point;

/* ——— Function prototypes —————————————————————————————————————————————————— */
/* Vec functions */
double	vec_norm(t_vec v);
double	vec_square(t_vec v);
double	vec_dot(t_vec v1, t_vec v2);
void	vec_normalize(t_vec *v);
void	vec_init(t_vec *v, double x, double y, double z);
t_vec	vec_mult_scalar(t_vec v, double d);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_vectoriel(t_vec u, t_vec v);
t_vec	vec_proj(t_vec a, t_vec b);

/* Valid functions */
int		int_valid(char *s);
int		long_valid(char *s);
int		float_valid(char *s);
int		double_valid(char *s);

bool	check_idx_string_tab(char **s, int idx);
bool	check_extention(char *str, char *key);

void	print_error(char *message);

#endif
