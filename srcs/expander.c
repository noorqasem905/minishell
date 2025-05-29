/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:37:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/29 14:32:52 by nqasem           ###   ########.fr       */
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

int	append_expansion(char **expanded, char *content, int *i, t_cmd *cmd)
{
	char	*expand_var;

	expand_var = expantions(content, i, cmd);
	if (!expand_var)
		return (-1);
	*expanded = ft_strjoin_free(*expanded, expand_var);
	free(expand_var);
	if (!*expanded)
		return (-1);
	return (0);
}

static int	handle_quotes_and_expand(
	char **expanded, char *content, int *i, t_cmd *cmd)
{
	static int	flag_single = 0;
	static int	flag_double = 0;

	if (content[*i] == '\'' && !flag_double)
	{
		flag_single = !flag_single;
		return (append_char(expanded, content[(*i)++]));
	}
	else if (content[*i] == '"' && !flag_single)
	{
		flag_double = !flag_double;
		return (append_char(expanded, content[(*i)++]));
	}
	else if (content[*i] == '$' && !flag_single)
		return (append_expansion(expanded, content, i, cmd));
	else
		return (append_char(expanded, content[(*i)++]));
}

char	*expander_input(t_cmd **cmd)
{
	char	*expanded;
	char	*content;
	int		i;

	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	i = 0;
	content = (char *)(*cmd)->word->content;
	while (content[i])
	{
		if (handle_quotes_and_expand(&expanded, content, &i, *cmd) < 0)
		{
			free(expanded);
			return (NULL);
		}
	}
	return (expanded);
}
