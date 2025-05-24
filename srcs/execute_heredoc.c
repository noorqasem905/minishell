/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:54:15 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/24 14:48:56 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc_manger(t_cmd **cmd, char **file_loc)
{
	t_list	*current;
	int		num_here_doc;
	int		size;
	int		i_j[2];

	i_j[0] = 0;
	i_j[1] = 0;
	current = (*cmd)->word;
	while ((*cmd)->here_doc->pryority[i_j[0]] != '\0')
	{
		if ((*cmd)->here_doc->pryority[i_j[0]] >= 2)
		{
			size = sizeof_heredoc(current->content);
			if (size > 1023 || heredoc(current->content, &(file_loc[i_j[1]]),
					size) < 0)
			{
				perror("heredoc");
				return (-1);
			}
			i_j[1]++;
		}
		current = current->next;
		i_j[0]++;
	}
	return (0);
}

void	handle_here_doc_unlink(t_cmd **cmd, char **file_loc)
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
			perror("malloc");
			return (-1);
		}
		(*cmd)->here_doc->file_loc = (*file_loc);
		if (here_doc_manger(cmd, (*cmd)->here_doc->file_loc) < 0)
			return (65);
	}
	return (0);
}

int	manager_execution_heredoc(char *file, char **temp)
{
	char	*command;
	int		which;

	which = which_redirection_char(file);
	command = ft_strfchr(file, which);
	if (setup_extra_command_h(file, &command))
	{
		free(command);
		return (-1);
	}
	*temp = command;
	return (0);
}

int	execute_heredoc(char *file, t_cmd **cmd, int i, char **file_loc)
{
	char	**redirection_split;
	char	*temp;
	char	*str;
	char	*st;

	if (execute_heredoc_setup_exe(file, cmd, i, &temp) < 0)
		return (-1);
	if (execute_heredoc_manage_exeu(file, &str, cmd, temp) < 0)
		return (-1);
	st = ft_strjoin(temp, str);
	if (execute_heredoc_redirection
		(&redirection_split, str, st, (*cmd)->env) < 0)
	{
		if (temp)
			free(temp);
		return (-1);
	}
	if (temp)
		free(temp);
	return (0);
}
