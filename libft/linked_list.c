/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:27:15 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/03 22:33:52 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insertend(t_list **root, void *new_value, int *flag)
{
	t_list	*new_node;
	t_list	*curr;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		*flag = 12;
		return ;
	}
	new_node->content = new_value;
	new_node->next = NULL;
	if (*root == NULL)
	{
		(*root) = new_node;
		return ;
	}
	curr = *root;
	while (curr->next)
	{
		curr = curr->next;
	}
	curr->next = new_node;
}