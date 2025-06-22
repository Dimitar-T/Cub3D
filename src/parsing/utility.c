/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:24:48 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 17:25:52 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exit_fail(char *message, t_data *game)
{
	if (message != NULL)
		write(2, message, ft_strlen(message));
	if (game != NULL)
	{
		if (game->img)
			mlx_delete_image(game->mlx, game->img);
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
	if (message == NULL)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	check_for_dup(t_data **data)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if ((*data)->check_list[i] != 1)
			exit_fail("Cub3D: Error duplicate or missing configuration!\n",
				NULL);
	}
}
