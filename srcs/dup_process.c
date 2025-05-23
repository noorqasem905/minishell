/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:03:40 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/24 18:06:40 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_process_2_handle(t_cmd **cmd, t_list **current, char **env)
{
	if (run_buildin_execution(*cmd, *current) < 0)
		return (-1);
	if (ft_execve((*current)->content, env) == -1)
	{
		perror("Command not found");
		return (-1);
	}
	return (0);
}

int	dup_process_2(t_cmd **cmd, t_list **current, char **file_loc, int i)
{
	char	**redirection_split;
	char	**env;
	int		heredoc_idx;

	env = (*cmd)->env;
	if ((*cmd)->here_doc->pryority[i] >= 2)
	{
		// (*cmd)->who_am_i = 0;
		heredoc_idx = (*cmd)->here_doc->pryority[i] - 2;
		if (execute_heredoc((*current)->content, cmd, heredoc_idx, file_loc)
			== -1)
			return (-1);
	}
	else if (ft_strmchr((*current)->content, "<>"))
	{
		ft_printf("%2enter");
		if (ft_redirection((*current)->content, &redirection_split, env) < 0)
		{
			write(2, "Error: Invalid redirection\n\n", 27);
			return (-1);
		}
	}
	if (dup_process_2_handle(cmd, current, env) < 0)
		return (-1);
	return (0);
}

void	dup_process_handle(int size, int pipe_fd2[][2])
{
	int	j;

	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
}

int	dup_process(int *i, int size, int pipe_fd2[][2])
{
	if ((*i) != 0)
	{
		if (dup2(pipe_fd2[(*i) - 1][0], STDIN_FILENO) == -1)
		{
			dprintf(2, "pipe failed at index %d\n", (*i));
			perror("dup2");
			return (-1);
		}
	}
	if ((*i) != size - 1)
	{
		if (dup2(pipe_fd2[(*i)][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
	}
	dup_process_handle(size, pipe_fd2);
	return (0);
}

void	close_wait(pid_t pids[], int size, int pipe_fd2[][2], t_cmd **cmd)
{
	int	i;
	int	j;
	int	status;
	int	g_sig;

	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
	i = -1;
	while (++i < size && pids[i] && pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			(*cmd)->exit_status = WEXITSTATUS(status);
			if ((*cmd)->exit_status != 0)
				ft_printf("%2Error: Command failed with status %d\n",
					(*cmd)->exit_status);
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
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	free(pids);
	free(pipe_fd2);
}//need test and norm
