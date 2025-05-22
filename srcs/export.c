/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:18:35 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/22 18:31:06 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_env_var(char *env_var)
{
	char	*eq;
	int		name_len;
	char	*name;
	char	*value;

	eq = ft_strchr(env_var, '=');
	if (!eq)
	{
		ft_printf("declare -x %s\n", env_var);
		return ;
	}
	name_len = eq - env_var;
	name = ft_substr(env_var, 0, name_len);
	value = ft_strdup(eq + 1);
	if (!name || !value)
		return ;
	print_with_value(name, value);
	free(name);
	free(value);
}

static void	print_export(t_cmd *cmd)
{
	int	i;

	if (!cmd->env)
	{
		ft_printf("%2Error: Environment is not initialized.\n");
		cmd->exit_status = 1;
		return ;
	}
	i = 0;
	while (cmd->env[i])
	{
		print_env_var(cmd->env[i]);
		i++;
	}
}

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
	char	*temp;

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
	char	**tmp;
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
			handle_invalid(export->name[i]);
		else
		{
			j = get_env_j((*cmd)->env, export->name[i]);
			handle_added(cmd, export, i, j);
		}
		i++;
	}
}
