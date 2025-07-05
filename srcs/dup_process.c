/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:03:40 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 15:34:07 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_process_2(t_cmd **cmd, t_list **current, int i)
{
	char	**redirection_split;
	int		heredoc_idx;

	if ((*cmd)->here_doc->pryority[i] >= 2)
	{
		heredoc_idx = (*cmd)->here_doc->pryority[i] - 2;
		if (execute_heredoc((*current)->content, cmd, heredoc_idx)
			== -1)
			return (-1);
	}
	else if (ft_strmchr((*current)->content, "<>"))
	{
		(*cmd)->exit_status = 2;
		if (ft_redirection((*current)->content, &redirection_split, cmd) < 0)
		{
			if (((*cmd)->exit_status == 2
					|| (*cmd)->exit_status == 0) && (*cmd)->bulidin <= 0)
				ft_printf("%2syntax error near unexpected token `newline`\n");
			return (-1);
		}
	}
	if (dup_process_2_handle(cmd, current) < 0)
		return (-1);
	return (0);
}

int	dup_process(int *i, int size, int pipe_fd2[][2])
{
	if ((*i) != 0)
	{
		if (dup2(pipe_fd2[(*i) - 1][0], STDIN_FILENO) == -1)
		{
			ft_printf("%2pipe failed at index %d\n", (*i));
			perror("dup2");
			return (-1);
		}
	}
	if ((*i) != size - 1)
	{
		if (dup2(pipe_fd2[(*i)][1], STDOUT_FILENO) == -1)
		{
			ft_printf("%2dup2");
			return (-1);
		}
	}
	dup_process_handle(size, pipe_fd2);
	return (0);
}

int	close_wait2_exit(int status, t_cmd **cmd)
{
	int	g_sig;

	if (WIFEXITED(status))
	{
		(*cmd)->exit_status = WEXITSTATUS(status);
		if ((*cmd)->exit_status == 42)
			return (-1);
	}
	else if (WIFSIGNALED(status))
	{
		g_sig = WTERMSIG(status);
		if (g_sig == SIGINT)
			write(1, "\n", 1);
		else if (g_sig == SIGQUIT)
			ft_printf("Quit (core dumped)\n");
		(*cmd)->exit_status = 128 + g_sig;
	}
	return (0);
}

void	close_wait2(pid_t pids[], int size, t_cmd **cmd)
{
	int	status;
	int	i;

	i = -1;
	while (++i < size && pids[i] && pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (close_wait2_exit(status, cmd) < 0)
			return ;
	}
}

void	close_wait(pid_t pids[], int size, int pipe_fd2[][2], t_cmd **cmd)
{
	int	j;

	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
	close_wait2 (pids, size, cmd);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	free(pids);
	free(pipe_fd2);
}
//&& handle_here_doc_qouts((*current)->content) to rediection