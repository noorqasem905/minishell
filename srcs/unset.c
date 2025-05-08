/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:20:32 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/08 23:28:01 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void unset(char *name, t_cmd *cmd)
{
    int i;
    int j;
    int len;
    char **new_env;

    if (!is_valid(name))
    {
        ft_printf("unset: `%s`: not a valid identifier\n", name);
        return;
    }
    len = 0;
    while (cmd->env[len])
        len++;
    new_env = malloc(sizeof(char *) * len);
    if (!new_env)
        return;
    i = 0;
    j = 0;
    while (cmd->env[i])
    {
        if (ft_strncmp(cmd->env[i], name, ft_strlen(name)) == 0 &&
            cmd->env[i][ft_strlen(name)] == '=')
        {
                free(cmd->env[i]);
        }
        else
        {
            new_env[j++] = cmd->env[i];
        }
        i++;
    }
    new_env[j] = NULL;
    free(cmd->env);
    cmd->env = new_env;
}