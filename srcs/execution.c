/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/20 20:12:31 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
void print_saved_cmd1(t_list *saved_cmd) {
    t_list *current = saved_cmd;
    while (current != NULL) {
        ft_printf("Command: %s\n", (char *)current->content);
        current = current->next;
    }
}

int execution(t_cmd **cmd, char **env)
{
	int size;
    pid_t pid;
    int i;
	size = ft_lstsize((*cmd)->word);
	t_list *current = (*cmd)->word;
    int pipe_fd2[size][2];
	int	j;
    pid_t pids[size];

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
				errno = ENOENT;
				perror("Command not found");
				int k = -1;
				// while (++k < size)
	        	//     kill(pids[k], SIGKILL);
				exit(EXIT_FAILURE);
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
        int status;
        waitpid(pids[i], &status, 0);
        // if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        // {
		// 	errno = ENOENT;
		// 	int k = -1;
		// 	while (++k < size)
	    //         kill(pids[k], SIGKILL);
        //     break;
        // }
    }
	return (0);
}
/* 
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int execution(t_cmd **cmd, char **env)
{
    int size;
    pid_t pid;
    int i;
    size = ft_lstsize((*cmd)->word);
    t_list *current = (*cmd)->word;
    int pipe_fd2[size][2];
    int j;
    pid_t pids[size]; // Array to store child PIDs

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
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            // Set process group ID for all children
            setpgid(0, 0);

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
                killpg(0, SIGKILL); // Kill all child processes in the group
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Store child PID
            pids[i] = pid;

            // Set process group ID for the parent to manage children
            setpgid(pid, pids[0]);
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
        int status;
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
			int k = -1;
			while (++k < size)
			{
	            kill(pids[k], SIGKILL);
			}
            break;
        }
    }
    return (0);
} */
/* 
int madin(int argc, char *argv[], char **env)
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
} */

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