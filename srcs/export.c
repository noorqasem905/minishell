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



static char *trim_quotes(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
        return (ft_substr(str, 1, len - 2));
    return (ft_strdup(str));
}


static int is_valid(char *name)
{
    int i;

    if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
        return (0);
    i = 1;
    while (name[i] && name[i] != '=')
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static int get_env_j(char **env, char *name)
{
    int i;
    int len;

    i = 0;

    len = ft_strlen(name);

    while (env && env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0  && env[i][len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

static void print_export(t_cmd *cmd)
{
    int i = 0;
    char *eq;
    char *delete;
    int name_len;
    char *name;
    char *value;

    if (!cmd->env)
    {
        ft_printf("Error: Environment is not initialized.\n");
        return;
    }
    while (cmd->env[i])
    {
        eq = ft_strchr(cmd->env[i], '=');
        if (eq)
        {
            name_len = eq - cmd->env[i];
            name = ft_substr(cmd->env[i], 0, name_len);
            value = ft_strdup(eq + 1);
            if (value[0] == '\0')
                ft_printf("declare -x %s\n", name);
            else
            {
                delete = trim_quotes(value);
                ft_printf("declare -x %s=\"%s\"\n", name, delete);
                free(delete);
            }
            free(name);
            free(value);
        }
        else
            ft_printf("declare -x %s\n", cmd->env[i]);
        i++;
    }
}

static void update_env(char **env, int j, char *name, char *value)
{
    char *new_name;
    char *temp;

    temp = ft_strjoin(name, "=");
    new_name = ft_strjoin(temp, value);
    free(temp);
    free(env[j]);
    env[j] = new_name;
}

static char **add_env(char **env, char *name, char *value)
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
        new_env[j] = env[j];
        j++;
    }
    temp = ft_strjoin(name , "=");
    new_name = ft_strjoin(temp, value);
    free(temp);
    new_env[i] = new_name;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}


void robo_export(t_cmd *cmd, t_exp *export)
{
	int i;
    int j;
	
	i = 0;
    if (export->name[0] == NULL)
    {
        if (!cmd->env)
        {
            ft_printf("%2ERROoRR");
            return;
        }
        print_export(cmd);
    }
	while (export->name[i])
	{
        if (!is_valid(export->name[i]))
        {
            ft_printf("%2export: `%s`: not a valid identifier\n", export->name[i]);
            i++;
            continue;
        }
        j = get_env_j(cmd->env, export->name[i]);
        if (j != -1)
            update_env(cmd->env, j, export->name[i], export->value[i]);
        else
            cmd->env = add_env(cmd->env, export->name[i], export->value[i]);
        i++;
	}
}
