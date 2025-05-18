/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:14:40 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/30 19:18:33 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char *trim_quotes(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
        return (ft_substr(str, 1, len - 2));
    return (ft_strdup(str));
}
int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' 
		|| c == '\f' || c == '\r');
}

int is_valid(char *name)
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



