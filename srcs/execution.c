/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/23 13:55:09 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	print_saved_cmd1(t_list *saved_cmd)
{
	t_list	*current;

	current = saved_cmd;
	while (current != NULL)
	{
		ft_printf("Command: %s\n", (char *)current->content);
		current = current->next;
	}
}

int	execution(t_cmd **cmd, char **env)
{
	int		i;
	int		j;
	int		k;
	int		size;
	int		status;
	t_list	*current;
	pid_t	pids[size];
	int		pipe_fd2[size][2];

	size = ft_lstsize((*cmd)->word);
	current = (*cmd)->word;
	i = 0;
	j = 0;
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
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			if (i != 0)
			{
				if (dup2(pipe_fd2[i - 1][0], STDIN_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (i != size - 1)
			{
				if (dup2(pipe_fd2[i][1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			j = 0;
			while (j < size - 1)
			{
				close(pipe_fd2[j][0]);
				close(pipe_fd2[j][1]);
				j++;
			}
			if (ft_execve(current->content, env) == -1)
			{
				perror("Command not found");
				return (-1);
			}
		}
		if (i > 0)
			close(pipe_fd2[i - 1][0]);
		if (i < size - 1)
			close(pipe_fd2[i][1]);
		current = current->next;
		i++;
	}
	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
	i = -1;
	while (++i < size)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			errno = ENOENT;
			k = -1;
			while (++k < size)
				kill(pids[k], SIGKILL);
			break ;
		}
	}
	return (0);
}
