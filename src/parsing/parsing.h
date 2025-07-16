/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:36:05 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/26 15:52:53 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"
# include "../cub3d.h"
# include "../init/init.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
	
char	**ft_split_plus(char *str, char *charset);
void	check_for_dup(t_data **data);
char	**copy_map(char **original);
void	find_player_position(char **map, int *out_y, int *out_x);
void	validate_texture_path(char *path, char *key, t_data **data);
int		get_fd(char *str);
void	exit_fail(char *message, t_data *game);
t_data	*map_parsing(char **map);
void	rgb_range_checker(char *row, int f_or_c, t_data **data);
char	**file_parsing(char **argv);
void	flood_fill(char **map, int y, int x);
#endif