/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:26:37 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/09 19:50:10 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(char **env, int j, char *name, char *value)
{
	char	*new_name;
	char	*temp;

	temp = ft_strjoin(name, "=");
	new_name = ft_strjoin(temp, value);
	free(temp);
	free(env[j]);
	env[j] = new_name;
}

int	remove_leading_tabs(char **result)
{
	char	*tmp;
	int		m;
	int		kk;

	m = 0;
	while (result[0] && result[0][m] == '\t')
		m++;
	if (m > 0)
	{
		tmp = malloc(ft_strlen(result[0]) - m + 1);
		if (!tmp)
			return (-1);
		kk = 0;
		while (result[0][m])
			tmp[kk++] = result[0][m++];
		tmp[kk] = '\0';
		free(result[0]);
		result[0] = tmp;
	}
	return (0);
}
