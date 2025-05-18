/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:49:58 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/15 16:25:13 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_invalid(char *name)
{
	ft_printf("%2export: `%s`: not a valid identifier\n", name);
}
void error_export(t_cmd **cmd)
{
    ft_printf("%2ERROR EXPORT");
    (*cmd)->exit_status = 2;
}



void	print_with_value(char *name, char *value)
{
	char	*trimmed;

	if (value[0] == '\0')
		ft_printf("declare -x %s\n", name);
	else
	{
		trimmed = trim_quotes(value);
		ft_printf("declare -x %s=\"%s\"\n", name, trimmed);
		free(trimmed);
	}
}
int get_env_j(char **env, char *name)
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
void handle_added(t_cmd **cmd, t_exp *export, int i, int j)
{
    if (j != -1)
		update_env((*cmd)->env, j, export->name[i], export->value[i]);
	else
	{
		char **tmp = add_env((*cmd)->env, export->name[i], export->value[i]);
		frees_split((*cmd)->env);
		(*cmd)->env = tmp;
	}    
}