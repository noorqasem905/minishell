/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_expo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:32:38 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/18 20:02:57 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*helper_fun(char *env)
{
	char	*eq;
	char	*name;
	char	*value;
	char	*line;
	char	*tmp;

	eq = ft_strchr(env, '=');
	if (eq)
	{
		name = ft_substr(env, 0, eq - env);
		if (!name)
			return (NULL);
		value = ft_strdup(eq + 1);
		if (!value)
		{
			free(name);
			return (NULL);
		}
		line = ft_strjoin("declare -x ", name);
		free(name);
		if (!line)
		{
			free(value);
			return (NULL);
		}
		tmp = line;
		line = ft_strjoin(tmp, "=\"");
		free(tmp);
		if (!line)
		{
			free(value);
			return (NULL);
		}
		tmp = line;
		line = ft_strjoin(tmp, value);
		free(tmp);
		free(value);
		if (!line)
			return (NULL);
		tmp = line;
		line = ft_strjoin(tmp, "\"");
		free(tmp);
		if (!line)
			return (NULL);
		return (line);
	}
	else
	{
		return (ft_strjoin("declare -x ", env));
	}
}

void	save_export_to_expo(t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd->env && cmd->env[i])
		i++;
	cmd->expo = (char **)malloc((i + 1) * sizeof(char *));
	if (!cmd->expo)
		return ;
	while (j < i)
	{
		cmd->expo[j] = helper_fun(cmd->env[j]);
		j++;
	}
	cmd->expo[i] = NULL;
}