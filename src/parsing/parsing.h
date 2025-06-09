/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:36:05 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/04 16:07:33 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../cub3d.h"

char	**file_parsing(char **argv);
void	exit_fail(char *message);
int 	map_parsing(char **map);
void 	rgb_range_checker(char *row);

#endif