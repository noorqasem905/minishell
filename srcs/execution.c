/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/10 18:25:46 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int execution(t_cmd **cmd, char **env)
{
	pid_t pid1;

	if (!cmd || !(*cmd) || !(*cmd)->word)
	{
		perror("Invalid command structure");
		return (-1);
	}
	while ((*cmd)->word)
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			if (ft_execve((*cmd)->word->content, env) == -1)
				exit(EXIT_FAILURE);
		}
		printf("Command: %s\n", (char *)((*cmd)->word->content));
		(*cmd)->word = (*cmd)->word->next;
		waitpid(pid1, NULL, 0);
	}
	return (0);
}

int main(int argc, char *argv[], char **env)
{
	t_cmd *cmd;
	// char str[4][20] = {"ls -l", "grep .c", "wc -l"};
	char **str;
	int i = 0;
	str = malloc(sizeof(char *) * 4);
	while (i < 4)
	{
		str[i] = (char *)malloc(sizeof(char) * 20);
		i++;
	}
	
	str[0] = "ls -l";
	str[1] = "wc -l";
	str[2] = NULL;
	int flag = 0;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		perror("malloc");
		return (1);
	}
	if (!cmd)
	{
		perror("malloc");
		return (1);
	}
	i = 0;
	while (str[i] && i < ft_strlen(*str))
	{
		insertend(&cmd->word, str[i], &flag);
		printf("Command: %s\n", (char *)cmd->word->content);
		i++;
	}	
		execution(&cmd, env);
	free(cmd);
	return (0);
}

	/* int	maind(int argc, char *argv[], char **env)
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
 */