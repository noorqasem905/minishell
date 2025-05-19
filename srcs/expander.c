/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:37:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/18 16:26:18 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *name, char **env)
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

static char	*expantions(char *input, int *i, char **env, t_cmd *cmd)
{
	char	*name;
	char	*value;
	int		start;

	if (input[*i + 1] && input[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(cmd->exit_status));
	}
	if (!input[*i + 1] || (!ft_isalnum(input[*i + 1]) && input[*i + 1] != '_'))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	start = *i + 1;
	*i = start;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	name = ft_substr(input, start, *i - start);
	value = get_env_value(name, env);
	free(name);
	return (value);
}

char	*expander_input(t_list *input, char **env, t_cmd *cmd)
{
	char	*expanded;
	char	*expand_var;
	char	*temp;
	char	c[2];
	int		i;
	int		start;
	int		end;
	int		flag_single;
	int		flag_double;
	char	*content;

	expanded = ft_strdup("");
	start = 0;
	end = 0;
	flag_single = 0;
	flag_double = 0;
	i = 0;
	content = (char *)input->content;
	while (content[i])
	{
		if (content[i] == '\'' && !flag_double)
		{
			flag_single = !flag_single;
			i++;
		}
		else if (content[i] == '\"' && !flag_single)
		{
			flag_double = !flag_double;
			i++;
		}
		else if (content[i] == '$' && !flag_single)
		{
			expand_var = expantions(content, &i, env, cmd);
			temp = ft_strjoin(expanded, expand_var);
			free(expanded);
			free(expand_var);
			expanded = temp;
		}
		else
		{
			c[0] = content[i++];
			c[1] = '\0';
			temp = ft_strjoin(expanded, c);
			free(expanded);
			expanded = temp;
		}
	}
	return (expanded);
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
