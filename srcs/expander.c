/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:37:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/26 17:07:35 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *name, t_cmd *cmd)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], name, len) && cmd->env[i][len] == '=')
		{
			return (ft_strdup(cmd->env[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

static char	*expantions(char *input, int *i, t_cmd *cmd)
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
	value = get_env_value(name, cmd);
	free(name);
	return (value);
}

void	append_expansion(char **expanded, char *content, int *i, t_cmd *cmd)
{
	char	*expand_var;

	expand_var = expantions(content, i, cmd);
	*expanded = ft_strjoin_free(*expanded, expand_var);
	free(expand_var);
}

char	*expander_input(t_cmd **cmd)
{
	char	*expanded;
	int		i;
	int		flag_single;
	int		flag_double;
	char	*content;

	expanded = ft_strdup("");
	flag_single = 0;
	flag_double = 0;
	i = 0;
	content = (char *)(*cmd)->word->content;
	while (content[i])
	{
		if (content[i] == '$' && !flag_single)
			append_expansion(&expanded, content, &i, *cmd);
		else
			append_char(&expanded, content[i++]);
	}
	return (expanded);
}
