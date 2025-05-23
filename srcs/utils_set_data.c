/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:35:32 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/23 14:45:19 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_closed(char *input)
{
	int	i;
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dquote == 0)
			squote = !squote;
		else if (input[i] == '"' && squote == 0)
			dquote = !dquote;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (0);
}

int	save_data(char **input, t_cmd **cmd, int *flag, char ***temp)
{
	int	size;
	int	iterator;

	*flag = 0;
	if (*temp == NULL)
	{
		perror("ft_split");
		return (-1);
	}
	size = ft_2dlen(*temp);
	if (size == 0)
		return (*flag = -3);
	(*cmd)->word = NULL;
	iterator = -1;
	while (++iterator < size)
	{
		if ((*temp)[iterator] != NULL)
		{
			insertend(&((*cmd)->word), (*temp)[iterator], flag);
			if (*flag == 12)
				break ;
		}
	}
	return (0);
}

int	check_no_pipe(char *input)
{
	int	i;

	i = 0;
	ft_strchr(input, '|');
	while (input[i])
	{
		if (input[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe_input(char *input)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input)
		return (-1);
	if (input[i] && input[i] == '|' || input[ft_strlen(input) - 1] == '|')
		return (-1);
	while (input[i])
	{
		if (input[i] != '|' && input[i] != ' ')
			pipe_count = 0;
		else if (input[i] == '|')
			pipe_count++;
		if (pipe_count > 1)
			return (-1);
		i++;
	}
	if (pipe_count > 0)
		return (-1);
	return (0);
}
