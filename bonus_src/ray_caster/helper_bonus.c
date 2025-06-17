/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/17 16:56:08 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

int	door_distance(int map_x, int map_y, t_player *player)
{
	double	distance;

	distance = hypot(player->px - (map_x * 64 + 32), player->py - (map_y * 64
				+ 32));
	if (distance <= 100)
		return (1);
	else
		return (0);
}
