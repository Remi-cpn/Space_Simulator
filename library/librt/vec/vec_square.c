/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:07:31 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 11:21:21 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

double	vec_square(t_vec v)
{
	const double	x = v.x;
	const double	y = v.y;
	const double	z = v.z;

	return (x * x + y * y + z * z);
}
