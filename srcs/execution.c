/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 18:53:27 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution_setup_process(int size, int (**pipe_fd2)[2], pid_t **pids)
{
	(*pids) = malloc((size + 1) * sizeof(pid_t));
	if (!(*pids))
		return (-1);
	(*pipe_fd2) = malloc((size + 1) * sizeof(int [2]));
	if (!*pipe_fd2)
		return (free_err_ret(NULL, (*pids), NULL, -1));
	(*pids)[size] = '\0';
	return (0);
}

int	execution_process(t_cmd **cmd)
{
	t_list	*current;
	pid_t	*pids;
	int		(*pipe_fd2)[2];
	int		ret;
	int		size;

	size = ft_lstsize((*cmd)->word);
	if (execution_setup_process(size, &pipe_fd2, &pids) < 0)
		return (-1);
	(*cmd)->current = (*cmd)->word;
	ret = open_pipe(cmd, size, pipe_fd2);
	if (ret != 0)
		return (ret);
	if (child_process(cmd, &current, pipe_fd2, pids) < 0)
	{
		free(pipe_fd2);
		return (free_err_ret("NULL", pids, NULL, -1));
	}
	close_wait(pids, size, pipe_fd2, cmd);
	if ((*cmd)->exit_status == 42)
		return (-1);
	return (0);
}

int	execution(t_cmd **cmd)
{
	t_list	*current;
	char	**file_loc;
	int		one_command;
	int		ret;

	one_command = 0;
	if ((*cmd)->word->next == NULL && ft_strchr
		((*cmd)->word->content, 'e')
		&& ft_strncmp(ft_strchr((*cmd)->word->content,
				'e'), "exit", 4) == 0)
		one_command = -1;
	ret = setup_execution(cmd);
	if (ret != 0)
		return (ret);
	ret = setup_execution_heredoc(cmd, &file_loc);
	if (ret != 0)
		return (ret);
	expand_cmds(cmd, (*cmd)->input);
	ret = execution_process(cmd);
	if (ret != 0)
		return (ret);
	handle_here_doc_unlink(cmd, file_loc);
	return (one_command);
}

void	child_process_close(int pipe_fd2[][2], pid_t pids[], int i, int size)
{
	if (i > 0)
		close(pipe_fd2[i - 1][0]);
	if (i < size - 1)
		close(pipe_fd2[i][1]);
}

int	child_process(t_cmd **cmd, t_list **current, int pipe_fd2[][2],
		pid_t pids[])
{
	int	size;
	int	i;

	i = -1;
	size = ft_lstsize((*cmd)->word);
	while (++i < size)
	{
		(pids)[i] = fork();
		if ((pids)[i] < 0)
		{
			perror("fork");
			return (-1);
		}
		if ((pids)[i] == 0)
		{
			if (dup_process(&i, size, pipe_fd2) == -1)
				return (-1);
			if (dup_process_2(cmd, (&(*cmd)->current),
					(*cmd)->here_doc->file_loc, i) == -1)
				return (-1);
		}
		child_process_close(pipe_fd2, pids, i, size);
		(*cmd)->current = (*cmd)->current->next;
	}
	return (0);
}
