/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:43:05 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/22 19:28:00 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection_check2free(char **temp, char ***redirection_split)
{
	if (*temp != NULL)
		free(*temp);
	if (*redirection_split)
		frees_split(*redirection_split);
	return (-1);
}

int	setup_handle_redirection(char *input, char ***redirection_split,
		char **temp, char **temp2)
{
	int	ret;

	ret = setup_redirection(input, temp, temp2);
	if (ret < 0)
		return (-1);
	if (!(*temp2))
	{
		free(*temp);
		return (-1);
	}
	*redirection_split = ft_mult_split(*temp2, "<> ");
	if (!*redirection_split)
	{
		free(*temp);
		free(*temp2);
		return (-1);
	}
	return (ret);
}

int	error_redirection(char **redirection_split, char *command, char *temp2,
		char *temp)
{
	if (!redirection_split)
	{
		free(command);
		free(temp);
		free(temp2);
		return (-1);
	}
	return (0);
}

int	error_process_redirection(char ***redirection_split, char **temp,
		char *input, char **temp3)
{
	*temp3 = ft_strmchr(input, "<>");
	if (!temp3)
	{
		redirection_check2free(temp, redirection_split);
		return (-1);
	}
	return (0);
}

int	error_ft_execute_redirection(char *temp, char *command, char **robo_env)
{
	if (ft_execve(command, robo_env) == -1)
	{
		if (command)
			free(command);
		if (temp)
			free(temp);
		perror("Command not found");
		return (-1);
	}
	free(command);
	free(temp);
	return (0);
}
