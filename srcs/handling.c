/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:40:01 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/23 14:24:47 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_err_ret(char *message, char *free_it,
			char **free_splt, int ret_value)
{
	if (message)
		ft_printf("%2", message);
	if (free_it)
		free(free_it);
	if (free_splt)
		frees_split(free_splt);
	return (ret_value);
}

void	free_list(t_list **saved_cmd)
{
	t_list	*current;
	t_list	*next;

	current = *saved_cmd;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
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
