/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/30 19:07:26 by nqasem           ###   ########.fr       */
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

int	set_init(t_cmd **cmd, int size)
{
	int		i;

	i = 0;
	(*cmd)->pryority = malloc(sizeof(int) * (size + 1));
	if ((*cmd)->pryority == NULL)
	{
		perror("malloc");
		return (-1);
	}
	while (i < size)
	{
		(*cmd)->pryority[i] = 0;
		i++;
	}
	(*cmd)->pryority[i] = -1;
	return (0);
}

int		ft_strfind(char *str, char *c)
{
	int	i;
	int j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c[0])
		{
			j = 0;
			while (str[i + j] && str[i + j] == c[j])
				j++;
			if (c[j] == '\0' && ft_strlen(c) == j)
				return (1);
		}
		i++;
	}
	return (0);
}

int searching_here_doc(t_cmd **cmd)
{
	t_list	*current;
	int		check_error;
	char	*temp;
	int		i;

	current = (*cmd)->word;
	i = 0;
	while (current != NULL)
	{
		if (ft_strfind(current->content, "<<"))
		{
			(*cmd)->who_am_i = 13;
			temp = ft_strnstr(current->content, "<<", ft_strlen(current->content));
			check_error = handle_here_doc(temp);
			if (check_error < 0)
			{
				printf("error here doc\n");
				(*cmd)->exit_status = -14;
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}
int	execution(t_cmd **cmd, char **env)
{
	int		i;
	int		j;
	int		k;
	int		size;
	int		status;
	t_list	*current;
	char	**redirection_split;

	size = ft_lstsize((*cmd)->word);
	(*cmd)->pryority = NULL;
	(*cmd)->who_am_i = 0;
	// (*cmd)->exit_status = 0;
	if (searching_here_doc(cmd) == -1)
	{
		perror("Error in here doc");
		return (-13);
	}
	set_init(cmd, size);
	pid_t	pids[size];
	int		pipe_fd2[size][2];
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
		    dprintf(2, "pipe failed at index %d\n", i);
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
			return (-1);
		}
		if (pids[i] == 0)
		{
			if (i != 0)
			{
				if (dup2(pipe_fd2[i - 1][0], STDIN_FILENO) == -1)
				{
					dprintf(2, "pipe failed at index %d\n", i);
					perror("dup2");
 					return (-1);
				}
			}
			if (i != size - 1)
			{
				if (dup2(pipe_fd2[i][1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					return (-1);
				}
			}
			j = 0;
			while (j < size - 1)
			{
 					close(pipe_fd2[j][0]);
 					close(pipe_fd2[j][1]);
				j++;
			}
			if (ft_strmchr(current->content ,"<>") && (*cmd)->who_am_i != 13)
			{
				if(ft_redirection(current->content, &redirection_split, env) < 0)
				{
					write(2, "Error: Invalid redirection\n\n", 27);
					return (-1);
				}
			}
			if ((*cmd)->who_am_i == 13)
			{
				{
					write(2, "here doc\n", 9);
					return (-1);
				}
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
	while (++i < size && pids[i] && pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	        fprintf(stderr, "Error: Command failed with status %d\n", WEXITSTATUS(status));
	}
	return (0);
}
