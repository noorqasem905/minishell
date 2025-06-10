/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:49:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/10 17:05:53 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_char(char **expanded, char ch)
{
	char	c[2];

	c[0] = ch;
	c[1] = '\0';
	*expanded = ft_strjoin_free(*expanded, c);
	if (!*expanded)
		return (-1);
	return (0);
}

void	expand_cmds(t_cmd **cmd, char *input)
{
	char	*expanded_cmd;

	if (!cmd || !(*cmd))
		return ;
	expanded_cmd = NULL;
	if (ft_strchr(input, '|') || *cmd)
	{
	}
	(*cmd)->current = (*cmd)->word;
	while ((*cmd)->current != NULL)
	{
		expanded_cmd = expander_input(cmd, (*cmd)->current);
		if (expanded_cmd)
		{
			free((*cmd)->current->content);
			(*cmd)->current->content = expanded_cmd;
		}
		(*cmd)->current = (*cmd)->current->next;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	if (!temp)
		return (NULL);
	return (temp);
}
