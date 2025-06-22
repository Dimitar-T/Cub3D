/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:24:48 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 17:00:35 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void exit_fail(char *message, t_data *game)
{
	if (message != NULL)
		write(2, message, ft_strlen(message));
	if (game != NULL)
	{
		if (game->img)
			mlx_delete_image(game->mlx, game->img);
		if (game->d)
			mlx_delete_texture(game->d);
		if (game->tn)
			mlx_delete_texture(game->tn);
		if (game->ts)
			mlx_delete_texture(game->ts);
		if (game->te)
			mlx_delete_texture(game->te);
		if (game->tw)
			mlx_delete_texture(game->tw);
		if (game->mlx)
			mlx_terminate(game->mlx);
	}	
	gc_free_all();
	if(message == NULL)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
