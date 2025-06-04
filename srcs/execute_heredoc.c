/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:54:15 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 17:31:22 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc_manger(t_cmd **cmd, char **file_loc)
{
	t_list	*current;
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
				ft_printf("%2heredoc initialize\n");
				return (-1);
			}
			i_j[1]++;
		}
		current = current->next;
		i_j[0]++;
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

static int	st_protuction(char **st, char *temp, char *str)
{
	(*st) = ft_strjoin(temp, str);
	if (!(*st))
	{
		free_err_ret(NULL, str, NULL, -1);
		return (free_err_ret(NULL, temp, NULL, -1));
	}
	return (0);
}

int	execute_heredoc(char *file, t_cmd **cmd, int i)
{
	char	**redirection_split;
	char	*temp;
	char	*str;
	char	*st;

	if (execute_heredoc_setup_exe(file, cmd, i, &temp) < 0)
		return (-1);
	if (execute_heredoc_manage_exeu(file, &str, cmd, temp) < 0)
		return (-1);
	st_protuction(&st, temp, str);
	if (execute_heredoc_redirection
		(&redirection_split, str, st, cmd) < 0)
	{
		if ((*cmd)->exit_status != 127)
			(*cmd)->exit_status = 2;
		if (temp)
			free(temp);
		return (-1);
	}
	if (temp)
		free(temp);
	return (0);
}
