/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:58:48 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 17:18:05 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "../cub3d.h"

typedef struct s_garbage_collector
{
	struct s_garbage_collector	*next;
	void						*content;
}								t_garbage_collector;

void							*gc_malloc(size_t size);
void							gc_track(void *ptr);
void							gc_free_all(void);

#endif