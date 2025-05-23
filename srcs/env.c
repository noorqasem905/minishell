/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:26:29 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/23 14:43:27 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**my_env(char **env)
{
	int		i;
	char	**my_env;

	i = 0;
	while (env[i])
		i++;
	my_env = malloc(sizeof(char *) * (i + 1));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		if (!my_env[i])
		{
			while (--i >= 0)
				free(my_env[i]);
			free(my_env);
			return (NULL);
		}
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}
