/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:49:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/27 18:44:35 by nqasem           ###   ########.fr       */
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
	t_list	*current;
	char	*expanded_cmd;

	current = NULL;
	expanded_cmd = NULL;
	if (ft_strchr(input, '|'))
		return ;
	current = (*cmd)->word;
	while (current != NULL)
	{
		expanded_cmd = expander_input(cmd);
		if (!expanded_cmd)
			return ;
		free(current->content);
		current->content = expanded_cmd;
		current = current->next;
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
