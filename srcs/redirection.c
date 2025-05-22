/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/22 19:19:03 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_redirection(char *input, char **temp, char **temp2)
{
	char	state;
	int		mult;

	mult = check_redirection_mult(input);
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
	return (mult);
}

char	*get_redirection_command(char *temp, char **redirection_split,
		int iteritor)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (!temp || !redirection_split || !redirection_split[iteritor])
		return (NULL);
	while (i < ft_strlen(temp))
	{
		j = 0;
		if (temp[i] == redirection_split[iteritor][0])
		{
			k = i;
			while (temp[k] && temp[k] == redirection_split[iteritor][j])
			{
				k++;
				j++;
			}
			if (ft_strlen(redirection_split[iteritor]) == j)
				return (temp + k);
		}
		i++;
	}
	return (NULL);
}

int	process_redirections(char ***redirection_split, char **robo_env,
		char **temp3, int i)
{
	char	**tty;
	int		ccount_i[2];
	int		fd;

	ccount_i[0] = -1;
	ccount_i[1] = i;
	tty = ft_mult_split((*temp3), "<>");
	while (++ccount_i[0] < ft_2dlen(*redirection_split))
	{
		(*temp3) = ft_strmchr((*temp3), "<>");
		if (!(*temp3))
			break ;
		if (ft_execute_redirection(tty, ccount_i, &fd, (*temp3)) < 0)
		{
			if (*redirection_split)
				frees_split(*redirection_split);
			if (tty)
				frees_split(tty);
			dprintf(2, "Error: Invalid redirection\n");
			return (-1);
		}
		(*temp3)++;
	}
	frees_split(tty);
	frees_split(*redirection_split);
	return (0);
}

static int		error_process_redirection_free(char *command, char *temp)
{
	if (temp)
		free(temp);
	if (command)
		free(command);
	return (-1);
}

int	ft_redirection(char *input, char ***redirection_split, char **robo_env)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*command;
	int		ret;

	if (!input || !robo_env)
		return (-1);
	ret = setup_handle_redirection(input, redirection_split, &temp, &temp2);
	if (ret < 0)
		return (-1);
	if (extract_and_apply_redirection(&temp, temp2, redirection_split,
			&command) < 0)
		return (-1);
	if (error_process_redirection(redirection_split, &temp, input, &temp3) < 0)
		return(error_process_redirection_free(command, temp));
	if (process_redirections(redirection_split, robo_env, &temp3, ret) < 0)
		return(error_process_redirection_free(command, temp));
	if (error_redirection(*redirection_split, command, temp2, temp) < 0)
		return (-1);
	if (error_ft_execute_redirection(temp, command, robo_env) < 0)
		return (-1);
	return (0);
}

/*
int	main(int argc, char *arv[], char **robo_env)
{
	char	*inter;
	char	*temp;
	char	*temp2;
	char	**redirection_split;
	char	**redirection_data_split;
	int		mult;
	char *temp3;

	inter = "ls -l <fin<in < in > fin";
	ft_redirection(inter, &redirection_split, robo_env);
	return (0);
} */