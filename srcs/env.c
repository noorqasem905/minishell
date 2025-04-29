/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:26:29 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/29 19:12:02 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*char	**my_env(char **env)
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
}*/

char **my_env(char **env)
{
    int i = 0;
	int j = 0;
	
    while (env[i])
		i++;
    char **my_env = malloc(sizeof(char *) * (i + 1));
	if (!my_env)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	while (j < i)
    {
        my_env[j] = ft_strdup(env[j]);
        if (!my_env[j])
        {
            while (--j >= 0)
			{
				free(my_env[j]);
			}
            free(my_env);
            return (NULL);
        }
		j++;
    }
    my_env[i] = NULL;
    return my_env;
}


