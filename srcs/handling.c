/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:40:01 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/06 18:50:30 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_list(t_list **saved_cmd) {
    t_list *current;
    t_list *next;

    current = *saved_cmd;
    while (current != NULL) {
        next = current->next;
        free(current->content); // Free the duplicated content
        free(current);          // Free the node itself
        current = next;
    }
    *saved_cmd = NULL;
}

void	frees(t_list **root)
{
	t_list	*cur;
	t_list	*cur2;

	cur = *root;
	while (cur != NULL)
	{
		cur2 = cur;
		cur = cur->next;
		free(cur2);
	}
	free(cur);
	*root = NULL;
}
