/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:37:56 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/12 21:14:28 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
/* 
static char *get_env_value(char *name, char **env)
{
    int len;
    int i;
    
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
    return (NULL);
}

static char *expantions(char *input, int *i, char **env)
{
    char *name;
    char *value;
    int start;
    int end;

    start = *i + 1;
    while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
        (*i)++;
    end = *i;
    name = ft_substr(input, start, end - start);
    if (!name)
        return (NULL);
    value = get_env_value(name, env);
    free(name);
    return (value);
}

char *expander_input(t_list *input, char **env)
{
    char *expanded = ft_strdup("");
    char *expand_var;
    char *temp;
    char c[2];
    int i;
    int flag_single = 0;
    int flag_double = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '\'' && !flag_double)
        {
            flag_single = !flag_single;
            i++;
        }
        else if (input[i] == '\"' && !flag_single)
        {
            flag_double = !flag_double;
            i++;
        }
        else if (input[i] == '$' && !flag_single)
        {
            expand_var = expantions(input, &i, env);
            temp = ft_strjoin(expanded, expand_var);
            free(expanded);
            free(expand_var);
            expanded = temp;
        }
        else 
        {
            c[0] = input[i];
            c[1] = '\0';
            temp = ft_strjoin(expanded, c);
            free(expanded);
            expanded = temp;
            i++;
        }
    }
    return (expanded);
}
 */