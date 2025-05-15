/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:18:35 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/03 20:18:35 by aalquraa         ###   ########.fr       */
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
		return;
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

void update_env(char **env, int j, char *name, char *value)
{
    char *new_name;
    char *temp;

    temp = ft_strjoin(name, "=");
    new_name = ft_strjoin(temp, value);
    free(temp);
    free(env[j]);
    env[j] = new_name;
}

char **add_env(char **env, char *name, char *value)
{
    int i;
    int j;
    char **new_env;
    char *new_name;
    char *temp;

    i = 0;
    j = 0;
    while (env && env[i])
        i++;
    new_env = malloc(sizeof(char*) * (i + 2));
    if (!new_env)
        return (NULL);
    while (j < i)
    {
        new_env[j] = ft_strdup(env[j]);
        j++;
    }
    temp = ft_strjoin(name , "=");
    new_name = ft_strjoin(temp, value);
    free(temp);
    new_env[i] = new_name;
	new_env[i + 1] = NULL;
	return (new_env);
}

void robo_export(t_cmd **cmd, t_exp *export)
{
    char **tmp;
	int i;
    int j;

	i = 0;
    if (export->name[0] == NULL)
    {
        if (!(*cmd)->env)
        {
            error_export(cmd);
            return;
        }
        print_export((*cmd));
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


