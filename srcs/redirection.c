/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/23 21:38:39 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n",str, split[i]);
		i++;
	}
}

int	check_redirection(char *input)
{
	int	i;
	int	is_pipe;
	int	return_value;

	i = 0;
	is_pipe = 0;
	return_value = 0;
	while (input[i])
	{
		if (input[i] == '>' && is_pipe == 0)
		{
			if (input[i + 1] == '>')
				return (1);
			else
				return (2);
		}
		else if (input[i] == '<' || is_pipe == 1)
		{
			if (input[i] == '<')
			{
				return_value = 3;
				is_pipe = 1;
			}
			else if (input[i] == '>')
				return (4);
		}
		i++;
	}
	return (return_value);
}

int	check_redirection_mult(char *input, int type)
{
	int	mult;
	int	mult_2;
	int	i;
	int	handle;
	int	conflect;
	int	is_enter;
	int	is_file;

	mult = 0;
	mult_2 = 0;
	i = 0;
	handle = 0;
	conflect = 0;
	is_enter = 0;
	is_file = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			mult++;
			conflect++;
			if (is_enter > 0 && is_file == 0)
				return (-1);
			is_enter = 1;
			is_file = 0;
			if (input[i + 1] == '<' && handle == 0)
			{
				i++;
				handle = 1;
			}
			if (input[i + 1] == '>')
				return (-1);
		}
		else if (input[i] == '>')
		{
			mult_2++;
			conflect++;
			if (is_enter > 0 && is_file == 0)
				return (-1);
			is_enter = 2;
			is_file = 0;
			if (input[i + 1] == '>' && handle == 0)
			{
				i++;
				handle = 1;
			}
			if (input[i + 1] == '<')
				return (-1);
		}
		else if (input[i] != ' ' && input[i] != '>' && input[i] != '<')
		{
			conflect = 0;
			mult_2 = 0;
			mult = 0;
			is_enter = 0;
			is_file = 1;
		}
		if (mult > 1 || mult_2 > 1 || conflect > 1)
			return (-1);
		i++;
	}
	if (is_enter > 0 && is_file == 0)
		return (-1);
	if (mult > 1 || mult_2 > 1 || conflect > 1)
		return (-1);
	return (0);
}

int		setup_redirection(char *input, char **temp, char **temp2)
{
	char	state;
	int		redirection_type;
	int		mult;

	redirection_type = check_redirection(input);
 	mult = check_redirection_mult(input, redirection_type);
	if (mult == -1)
	{
		dprintf(2, "Error: Multiple redirections\n");
		return (-1);
	}
	state = ft_strmchr(input, "<>")[0];
	if (state == '<')
	{
		*temp = ft_strfchr(input, '<');
		*temp2 = ft_strchr(input, '<');
	}
	else
	{
		*temp = ft_strfchr(input, '>');
		*temp2 = ft_strchr(input, '>');
	}
	return (0);
}

int		ft_execute_redirection_p1(char **redirection_split, int ccount, int *fd)
{
	*fd = open(redirection_split[ccount], O_RDONLY);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}
int		ft_execute_redirection_p2(char **redirection_split, int ccount, int *fd)
{
	*fd = open(redirection_split[ccount], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

int		ft_execute_redirection(char **redirection_split, int ccount, int *fd, char *temp3, pid_t pid)
{
	if (pid == 0)
	{
			if (temp3[0] == '>')
			{
				ft_execute_redirection_p1(redirection_split, ccount, fd);
			}
			else if (temp3[0] == '<')
			{
				ft_execute_redirection_p2(redirection_split, ccount, fd);
			}
			else
			{
				dprintf(2, "Error: Invalid redirection\n");
				return (-1);
			}
			wait(NULL);
			char *cmd = "/usr/bin/ls";
			char *ags[] = {cmd, NULL};
			if (execve(cmd, ags, NULL) == -1)
			{
				perror("execve");
				return (-1);
			}
	}
	return (0);
}

int		ft_redirection(char *input, char ***redirection_split, char ***redirection_data_split)
{
	pid_t	pid;
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		ccount = -1;
	int		fd = -1;

	setup_redirection(input, &temp, &temp2);
	*redirection_data_split = ft_split(temp, ' ');
	*redirection_split = ft_mult_split(temp2, "<> ");
	temp3 = ft_strmchr(input, "<>");
	while (++ccount < ft_2dlen(*redirection_split))
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (ccount != 0)
			temp3 = ft_strmchr(temp3 + 1, "<>");
		ft_execute_redirection(*redirection_split, ccount, &fd, temp3, pid);
	}
	free(temp);
	return (0);
}

/* int	main(void)
{
	char	*inter;
	char	*temp;
	char	*temp2;
	char	**redirection_split;
	char	**redirection_data_split;
	int		redirection_type;
	int		mult;
	char *temp3;
 
	inter = "ls here_doc.c < da < b >a  ";
	ft_redirection(inter, &redirection_split, &redirection_data_split);
	return (0);
}
 */	// char *temp = NULL;
	// char file;
	// char **split = ft_split(inter, '<');
	// char **split = ft_split(inter, ' ');
	// int fd = open(split[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// int fd_read = open(split[1], O_RDONLY);
	// if (fd == -1)
	// {
	//     perror("open");
	//     return (-1);
	// }
	// if (dup2(fd, STDOUT_FILENO) == -1)
	// {
	//     perror("dup2");
	//     close(fd);
	//     return (-1);
	// }
	// if (dup2(fd_read, STDIN_FILENO) == -1)
	// {
	//     perror("dup2");
	//     close(fd);
	//     return (-1);
	// }
	// char *cmd = "/usr/bin/ls";
	// char *ags[] = {cmd, NULL};
	// dprintf(2, "Executing command: %s\n", split[0]);
	// if (execve(cmd,ags , NULL) == -1)
	// {
	//     perror("execve");
	//     return (-1);
	// }
	// close(fd);
/* Note */
/*
// i have to handle all cases of pipe <> else if eveything is ok


















 */