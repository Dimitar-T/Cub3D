/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:55:19 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 17:33:49 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static t_garbage_collector	**get_mem_list(void)
{
	static t_garbage_collector	*mem_list = NULL;

	return (&mem_list);
}

void	*gc_malloc(size_t size)
{
	t_garbage_collector	**mem_list;
	t_garbage_collector	*new_node;
	void				*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	mem_list = get_mem_list();
	new_node->content = ptr;
	new_node->next = *mem_list;
	*mem_list = new_node;
	return (ptr);
}

void	gc_track(void *ptr)
{
	t_garbage_collector	*current;
	t_garbage_collector	*new_node;
	t_garbage_collector	**mem_list;

	if (!ptr)
		return ;
	mem_list = get_mem_list();
	current = *mem_list;
	while (current)
	{
		if (current->content == ptr)
			return ;
		current = current->next;
	}
	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
		return ;
	new_node->content = ptr;
	new_node->next = *mem_list;
	*mem_list = new_node;
}

void	gc_free_all(void)
{
	t_garbage_collector	**mem_list;
	t_garbage_collector	*current;
	t_garbage_collector	*temp;

	mem_list = get_mem_list();
	if (!mem_list || !*mem_list)
		return ;
	current = *mem_list;
	while (current)
	{
		free(current->content);
		current->content = NULL;
		temp = current;
		current = current->next;
		free(temp);
	}
	*mem_list = NULL;
}
