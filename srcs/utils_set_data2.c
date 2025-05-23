/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set_data2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:39:47 by nqasem	           #+#    #+#             */
/*   Updated: 2025/05/23 14:44:40 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_saved_cmd(t_list *saved_cmd)
{
	t_list	*current;

	current = saved_cmd;
	while (current != NULL)
	{
		ft_printf("Command: %s\n", (char *)current->content);
		current = current->next;
	}
}

void	init_data(t_cmd **cmd)
{
	t_here_doc	*here_doc;

	here_doc = (*cmd)->here_doc;
	(*cmd)->word = NULL;
	(*cmd)->env = NULL;
	(*cmd)->expo = NULL;
	(*cmd)->pryority = NULL;
	(*cmd)->who_am_i = 0;
	(*cmd)->counter = 0;
	(*cmd)->index = 0;
	(*cmd)->here_doc->file_loc = NULL;
	(*cmd)->exit_status = 0;
	here_doc->counter = 0;
	here_doc->index = 0;
	here_doc->counter_total = 0;
	here_doc->pryority = NULL;
	here_doc->temp = NULL;
	here_doc->fd = 0;
}
