/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:35:32 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/04 20:50:59 by aalquraa         ###   ########.fr       */
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

static int	is_pipe_invalid(char *input, int *i)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	if (!input || (input[*i] == '|' && !input[*i + 1])
		|| (input[ft_strlen(input) - 1] == '|'))
		return (1);
	return (0);
}

static void	update_quotes(char c, int *squote, int *dquote)
{
	if (c == '\'' && *dquote == 0)
		*squote = !(*squote);
	else if (c == '"' && *squote == 0)
		*dquote = !(*dquote);
}

int	check_pipe_input(char *input)
{
	int	i;
	int	pipe_count;
	int	squote;
	int	dquote;

	i = 0;
	pipe_count = 0;
	squote = 0;
	dquote = 0;
	if (is_pipe_invalid(input, &i))
		return (-1);
	while (input[i])
	{
		update_quotes(input[i], &squote, &dquote);
		if (input[i] == '|' && !squote && !dquote)
			pipe_count++;
		else if (input[i] != ' ' && input[i] != '|' && !squote && !dquote)
			pipe_count = 0;
		if (pipe_count > 1)
			return (-1);
		i++;
	}
	if (pipe_count > 0)
		return (-1);
	return (0);
}
