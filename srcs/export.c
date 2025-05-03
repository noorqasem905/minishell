/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:20:17 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/03 17:01:03 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int is_valid_var(char *var)
{
    int i = 0;
    if (!ft_isalpha(var[i]) && var[i] != '_')
        return (0);
    i++;
    while (var[i])
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return (0);
        i++;
    }
    return (1);
}


static void	free_2d_array(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
static char **add_to_env(char **env, char *new_var)
{
    int len;
    int i;
    char **new_env;

    i = 0 ;
    len = ft_2dlen(env);
    new_env = malloc(sizeof(char *) * (len + 2));
    if (!new_env)
        return (NULL);
    while (i < len)
    {
        new_env[i] = ft_strdup(env[i]);
        i++;
    }
    new_env[len] = ft_strdup(new_var);
    new_env[len + 1] = NULL;
    free_2d_array(env);
    return (new_env);
}



static int compare_env(void *a, void *b)
{
    return ft_strcmp(*(char **)a, *(char **)b);
}


static void print_export(char **env)

{
    int i;
    int len;
    char **temp;
    char *eq;
    int key_len;
    i = 0;
    len = ft_2dlen(env);
    temp = malloc(sizeof(char *) * (len + 1));
    if (!temp)
    {
        ft_printf("export: malloc error\n");
        return;
    }
    while (i < len)
    {
        temp[i] = ft_strdup(env[i]);
        i++;
    }
    temp[i] = NULL;
    i = 0;
    while (temp[i])
    {
        eq = ft_strchr(temp[i], '=');
        if (eq)
        {
            int key_len = eq - temp[i];
            ft_printf("declare -x ");
            write(1, temp[i], key_len);
            ft_printf("=\%s\n", eq + 1);
        }
        else
        {
            ft_printf("declare -x %s\n", temp[i]);
        }
        free(temp[i]);
        i++;
    }
    free(temp);
}

static int find_env(char *key, char **env)
{
    int i;
    char *eq;

    i = 0;
    while (env[i])
    {
        eq = ft_strchr(env[i], '=');
        if (eq)
        {
            if (ft_strncmp(key, env[i], eq - env[i]) == 0)
                return (i);
        }
        i++;
    }
    return (-1);
}
void    export_t(char **var, t_cmd *cmd)
{
    int i = 1;
    int index;
    int key_len;
    char *eq;
    char *key;
    char *value;

    if (!var[1])
    {
        print_export(cmd->env);
        return;
    }
    while (var[i])
    {
        eq = ft_strchr(var[i], '=');
        if (eq)
            key_len = eq - var[i];
        else
            key_len = ft_strlen(var[i]);
        key = ft_substr(var[i], 0, key_len);
        value = ft_substr(var[i], key_len, ft_strlen(var[i]) - key_len);
        printf("%s\n", key);
        printf("%s\n", value);
        /*if (!is_valid_var(key))
        {
            ft_printf("export: '%s': not a valid identifier\n", var[i]);
            free(key);
            i++;
            continue;
        }
        if (eq)
        {
            index = find_env(key, cmd->env);
            if (index != -1)
            {
                free(cmd->env[index]);
                cmd->env[index] = ft_strdup(var[i]);
            }
            else
                cmd->env = add_to_env(cmd->env, var[i]);
        }
        else if (!find_env(key, cmd->env))
            cmd->env = add_to_env(cmd->env, var[i]);
        free(key);*/
        i++;
    }
}


