/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exection_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:53:55 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/05 13:05:20 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_here_doc_nolink(t_cmd **cmd)
{
	int	no;

	no = 0;
	while (no < (*cmd)->here_doc->counter)
	{
		if ((*cmd)->here_doc->file_loc[no])
		{
			free((*cmd)->here_doc->file_loc[no]);
			(*cmd)->here_doc->file_loc[no] = NULL;
		}
		no++;
	}
	if ((*cmd)->here_doc->file_loc)
	{
		free((*cmd)->here_doc->file_loc);
		(*cmd)->here_doc->file_loc = NULL;
	}
}

void	handle_here_doc_unlink(t_cmd **cmd)
{
	int	no;

	no = 0;
	while (no < (*cmd)->here_doc->counter)
	{
		if ((*cmd)->here_doc->file_loc[no])
		{
			unlink((*cmd)->here_doc->file_loc[no]);
			free((*cmd)->here_doc->file_loc[no]);
			(*cmd)->here_doc->file_loc[no] = NULL;
		}
		no++;
	}
	if ((*cmd)->here_doc->file_loc)
	{
		free((*cmd)->here_doc->file_loc);
		(*cmd)->here_doc->file_loc = NULL;
	}
}

int	setup_execution_heredoc(t_cmd **cmd, char ***file_loc)
{
	(*file_loc) = NULL;
	if ((*cmd)->here_doc->counter > 0)
	{
		(*file_loc) = malloc(sizeof(char *) * ((*cmd)->here_doc->counter + 1));
		if (!file_loc)
		{
			ft_printf("%2malloc\n");
			return (-1);
		}
		(*cmd)->here_doc->file_loc = (*file_loc);
		if (here_doc_manger(cmd, (*cmd)->here_doc->file_loc) < 0)
		{
			(*cmd)->exit_status = 2;
			return (65);
		}
		if (g_exit_status == 130)
		{
			(*cmd)->exit_status = 130;
			return (130);
		}
	}
	return (0);
}
