/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/20 17:53:44 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

int	door_distance(int map_x, int map_y, t_player *player, t_data *game)
{
	double	distance;

	distance = hypot(player->px - (map_x * game->tile + game->tile / 2), player->py - (map_y * game->tile + game->tile / 2));
	if (distance <= 100)
		return (1);
	else
		return (0);
}
