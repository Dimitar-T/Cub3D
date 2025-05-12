/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:17:12 by jwardeng          #+#    #+#             */
/*   Updated: 2024/10/23 18:16:59 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

// allocates node and changes content
// returns new node
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/* int	main(void)
{
	t_list *node;
	int *value;
	t_list *new;
	t_list *supernew;

	value = 0;
	node = ft_lstnew("hallo Ryan, ");
	new = ft_lstnew("wir koennen einen Roman schreiben, ");
	supernew = ft_lstnew("in diesen schoenen nodes");

	printf("node1: %s\n", node->content);
	printf("node2: %s\n", new->content);
	printf("node3: %s\n", supernew->content);

		// printf("content: %s\n", node->content);
		ft_lstadd_back(&node, new);
		// printf("new Node: %s\n", new->content);
		// value = ft_lstsize(new);
		// printf("Listsize: %d\n", value);
		ft_lstadd_back(&new, supernew);
		// value = ft_lstsize(supernew);
		// printf("Listsize: %d\n", value);
		ft_lstiter(supernew, ft_toupper);
		printf("%c\n", supernew->content);
} */