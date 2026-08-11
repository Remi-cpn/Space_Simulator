/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_vectoriel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:35:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/20 17:57:00 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

t_vec	vec_vectoriel(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = (u.y * v.z) - (u.z * v.y);
	w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
	return (w);
}
