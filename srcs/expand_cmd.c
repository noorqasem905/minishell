/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:52:14 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/15 18:25:26 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*get_env_value(char *name, char **env)
{
	int	len;
	int	i;
	
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
		{
			return (ft_strdup(env[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	expand_cmds(t_cmd **cmd, char **env)
{
	t_list	*current;
	char	*expanded_cmd;

	current = (*cmd)->word;
	while (current != NULL)
	{
		expanded_cmd = expander_input(current, env, *cmd);
		free(current->content);
		current->content = expanded_cmd;
		current = current->next;
	}
}
