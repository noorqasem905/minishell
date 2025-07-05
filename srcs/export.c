/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:18:35 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/12 18:25:33 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_name_value(char *name, char *value)
{
	char	*temp;
	char	*new_name;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	new_name = ft_strjoin(temp, value);
	free(temp);
	return (new_name);
}

char	**add_env(char **env, char *name, char *value)
{
	int		i;
	int		j;
	char	**new_env;
	char	*new_name;

	i = 0;
	j = -1;
	while (env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	while (++j < i)
		new_env[j] = ft_strdup(env[j]);
	if (!value)
		new_name = ft_strdup(name);
	else
	{
		new_name = join_name_value(name, value);
	}
	new_env[i] = new_name;
	new_env[i + 1] = NULL;
	return (new_env);
}

void	robo_export(t_cmd **cmd, t_exp *export)
{
	int		i;
	int		j;

	i = 0;
	if (export->name[0] == NULL)
	{
		if (!(*cmd)->env)
		{
			error_export(cmd);
			return ;
		}
	}
	while (export->name[i])
	{
		if (!is_valid(export->name[i]))
			handle_invalid(export->name[i], cmd);
		else
		{
			j = get_env_j((*cmd)->env, export->name[i]);
			handle_added(cmd, export, i, j);
		}
		i++;
	}
}
