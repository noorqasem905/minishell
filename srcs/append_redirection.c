/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:55:46 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 17:00:15 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_append_redirection(int heredoc_append[])
{
	heredoc_append[0] = 1;
	heredoc_append[1] = 1;
}

int	check_append_redirection(char **curr, int heredoc_append[])
{
	if (*(*curr) == '<' && *((*curr) + 1) == '<'
		&& heredoc_append[0] && heredoc_append[1])
	{
		heredoc_append[0] = 0;
		(*curr) += 2;
		return (2);
	}
	if (*(*curr) != '<' && *(*curr) != '>' && !ft_isspace(*(*curr)))
		init_append_redirection(heredoc_append);
	if (*(*curr) == '>' && *((*curr) + 1) == '>'
		&& heredoc_append[0] && heredoc_append[1])
	{
		heredoc_append[1] = 0;
		(*curr) += 2;
		return (2);
	}
	if (ft_isspace(*(*curr)))
	{
		(*curr)++;
		return (2);
	}
	if (((*(*curr) == '<') || (*(*curr) == '>'))
		&& heredoc_append[0] && heredoc_append[1])
		(*curr)++;
	return (0);
}

int	check_extra_redirection(char *tmp)
{
	int		heredoc_append[2];
	char	*curr;
	char	*s;

	s = ft_strdup(tmp);
	curr = s;
	init_append_redirection(heredoc_append);
	while (*curr)
	{
		if (check_append_redirection(&curr, heredoc_append))
			continue ;
		if (*curr != '<' && *curr != '>')
			init_append_redirection(heredoc_append);
		else
		{
			free(s);
			return (-1);
		}
		curr++;
	}
	free(s);
	return (0);
}

int	ft_heredoc_redirection_manager(char *file, char **str)
{
	char	*tmp2;
	char	*tmp;
	int		j;

	j = 0;
	*str = NULL;
	tmp = ft_strmchr(file, "<>");
	while (tmp != NULL)
		if (ft_heredoc_redirection_manager_2(&j, str, &tmp) < 0)
			return (-1);
	if (j)
	{
		tmp2 = ft_strjoin(">", *str);
		free(*str);
		*str = tmp2;
	}
	return (0);
}
