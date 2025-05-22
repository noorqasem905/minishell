/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:40:51 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/22 17:42:14 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	free_it(char **str, size_t i)
{
	while (i != 0)
	{
		free(str[i]);
		i--;
	}
	free(str[i]);
	free(str);
}

char	*trim_quotess(char *str)
{
	return (ft_strtrim(str, "\""));
}

void	free_exp(t_exp *export)
{
	frees_newsplit(export->name);
	frees_newsplit(export->value);
	free(export);
}
