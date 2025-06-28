/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:29:58 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/26 16:34:49 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_n(char *line, int *i)
{
	int	j;
	int	no_newline;

	no_newline = 0;
	while (line[*i] == '-' && line[*i + 1] == 'n')
	{
		j = *i + 2;
		while (line[j] == 'n')
			j++;
		if (line[j] == ' ' || line[j] == '\0')
		{
			no_newline = 1;
			*i = j;
			while (line[*i] == ' ')
				(*i)++;
		}
		else
			break ;
	}
	return (no_newline);
}

static void	print_line(char *line, int *i)
{
	int	quote;

	quote = 0;
	while (line[*i])
	{
		if (!quote && (line[*i] == '\'' || line[*i] == '"'))
		{
			quote = line[(*i)++];
			continue ;
		}
		if (quote && line[*i] == quote)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if (!quote && line[*i] == ' ')
		{
			write(1, " ", 1);
			while (line[*i] == ' ')
				(*i)++;
			continue ;
		}
		write(1, &line[*i], 1);
		(*i)++;
	}
}

int	ft_echo(t_list *command)
{
	char	*line;
	int		i;
	int		flag_newline;

	line = command->content;
	i = 0;
	flag_newline = 0;
	if (ft_strncmp(line, "echo", 4) == 0)
		i = 4;
	while (line[i] && line[i] == ' ')
		i++;
	flag_newline = skip_n(line, &i);
	print_line(line, &i);
	if (!flag_newline)
		write(1, "\n", 1);
	return (0);
}