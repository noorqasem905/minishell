/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/09 20:18:48 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int execution(t_cmd **cmd, char **env)
{
    pid_t    pid1;
    pid_t    pid2;

    pid1 = fork();
	if (pid1 == 0)
		ft_execve((*cmd)->word, env);
	pid2 = fork();
	if (pid2 == 0)
	    ft_execve((*cmd)->word, env);
    wait(NULL);
	wait(NULL);
    return (0);
}

int	maind(int argc, char *argv[], char **env)
{
	int		p_fd[2];
	pid_t	f1;
	pid_t	f2;

	if (argc != 5)
	{
		perror("Invalid number of arguments");
		return (-1);
	}
	if (pipe(p_fd) == -1)
		perror("Error in Pipe");
	f1 = fork();
	if (f1 == 0)
		child_file(p_fd, argv, env);
	f2 = fork();
	if (f2 == 0)
		parent_file(p_fd, argv, env);
	close(p_fd[1]);
	close(p_fd[0]);
	wait(NULL);
	if ((wait(NULL)) == f1)
		{}// id = f1;
	return (0);
}
