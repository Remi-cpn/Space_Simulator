/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult_scalar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:08:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 11:21:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

t_vec	vec_mult_scalar(t_vec v_src, double d)
{
	t_vec	v;

	v.x = v_src.x * d;
	v.y = v_src.y * d;
	v.z = v_src.z * d;
	return (v);
}
