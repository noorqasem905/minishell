/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulidin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:22:50 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/29 19:59:55 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int is_valid_var(char *var)
{
    if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
        return (0);
    while (*var)
    {
        if (!ft_isalnum(*var) && *var != '_')
            return (0);
        var++;
    }
    return (1);
}


static char **add_to_env(char **robo_env, const char *var, const char *value)
{
    int i;
    int j;
    size_t var_len;
    
    i = 0;
    j = 0;
    var_len = ft_strlen(var);
    while ((*robo_env)[i])
    {
        if (ft_strncmp(robo_env[i], var, var_len) == 0 && robo_env[i][var_len] == '=')
        {
            free(robo_env[i]);
            char *tmp = ft_strjoin(var, "=");
            robo_env[i] = ft_strjoin(tmp, value);
            free(tmp);
            return (robo_env);
        }
        i++;
    }
    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    while(j < i)
    {
        new_env[j] = ft_strdup(robo_env[j]);
        j++;
    }

    char *tmp = ft_strjoin(var, "=");
    new_env[i] = ft_strjoin(tmp, value);
    free(tmp);
    new_env[i + 1] = NULL;

    frees_split(robo_env);
    return (new_env);
}


char **export(char **var, char ***robo_env)
{
    int i;
    char *eq;
    int var_len;
    char *key;
    char *value;

    var_len = 0;
    i = 0;
    if (!var[1])
    {
        while ((*robo_env)[i])
        {
            eq = ft_strchr((*robo_env)[i], '=');
            if (eq)
            {
                var_len = eq - (*robo_env)[i];
                ft_printf("declare -x ");
                write(1, (*robo_env)[i], var_len + 1);
                ft_printf("\"%s\"\n", eq + 1);
            }
            else
            {
                ft_printf("declare -x %s\n", (*robo_env)[i]);
            }
            i++;
        }
        return(robo_env);
    }
    i = 1;
    while (var[i])
    {
        eq = ft_strchr(var[i], '=');
        
        if (eq)
        {
            int var_len = eq - var[i];
            key = ft_substr(var[i], 0, var_len);
            value = ft_strdup(eq + 1);

            if (is_valid_var(key))
                add_to_env(robo_env, key, value);
            else
                ft_printf("export: `%s` not a valid identifier\n", var[i]);

            free(key);
            free(value);
        }
        else
        {
            if (is_valid_var(var[i]))
                add_to_env(robo_env, var[i], "");
            else
                ft_printf("export: `%s`: not a valid identifier\n", var[i]);
        }
        i++;
    }
    return (robo_env);
}


