/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:49:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/22 20:02:52 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_char(char **expanded, char ch)
{
	char	c[2];

	c[0] = ch;
	c[1] = '\0';
	*expanded = ft_strjoin_free(*expanded, c);
}

void	expand_cmds(t_cmd **cmd)
{
	t_list	*current;
	char	*expanded_cmd;

	current = (*cmd)->word;
	while (current != NULL)
	{
		expanded_cmd = expander_input(cmd);
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
	return (temp);
}
