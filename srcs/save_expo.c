/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_expo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:32:38 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/18 18:42:49 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void save_export_to_expo(t_cmd *cmd)
{
    int i;
    int j;
    char *eq;
    char *name;
    char *value;
    char *output;
    
    i = 0;
    while (cmd->env && cmd->env[i])
        i++;
    cmd->expo = (char **)malloc((i + 1) * sizeof(char *));
    j = 0;
    while (cmd->env[j])
    {
        eq = ft_strchr(cmd->env[j], '=');
        if (eq)
        {
            name = ft_substr(cmd->env[j], 0, eq - cmd->env[j]);
            value = ft_strdup(eq + 1);
           output = ft_strjoin("declare -x ", name);
           output = ft_strjoin(output, "=\"");
           output = ft_strjoin(output, value);
           output = ft_strjoin(output, "\"");
            free(name);
            free(value);
        }
        else
        {
           output = ft_strjoin("declare -x ", cmd->env[j]);
        }
        cmd->expo[j] =output;
        j++;
    }
    cmd->expo[j] = NULL;
}
