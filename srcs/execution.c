/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/23 18:25:18 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_pipe(t_cmd **cmd, int size, int pipe_fd2[][2])
{
	int	i;

	i = 0;
	if (!cmd || !(*cmd) || !(*cmd)->word)
	{
		perror("Invalid command structure");
		return (-1);
	}
	if (size == 0)
	{
		perror("No commands to execute");
		return (-1);
	}
	while (i < size - 1)
	{
		if (pipe(pipe_fd2[i]) == -1)
		{
			dprintf(2, "pipe failed at index %d\n", i);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
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
	pids = malloc((size + 1) * sizeof(pid_t));
	pipe_fd2 = malloc((size + 1) * sizeof(int [2]));
	pids[size] = '\0';
	current = (*cmd)->word;
	ret = open_pipe(cmd, size, pipe_fd2);
	if (ret != 0)
		return (ret);
	if (child_process(cmd, &current, pipe_fd2, pids) < 0)
	{
		free(pipe_fd2);
		return (free_err_ret(NULL, pids, NULL, -1));
	}
	close_wait(pids, size, pipe_fd2);
	return (0);
}

int	execution(t_cmd **cmd)
{
	t_list	*current;
	char	**file_loc;
	int		ret;

	ret = setup_execution(cmd);
	if (ret != 0)
		return (ret);
	ret = setup_execution_heredoc(cmd, &file_loc);
	if (ret != 0)
		return (ret);
	ret = execution_process(cmd);
	if (ret != 0)
		return (ret);
	handle_here_doc_unlink(cmd, file_loc);
	return (0);
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
			if (dup_process_2(cmd, (current),
					(*cmd)->here_doc->file_loc, i) == -1)
				return (-1);
		}
		child_process_close(pipe_fd2, pids, i, size);
		(*current) = (*current)->next;
	}
	return (0);
}
