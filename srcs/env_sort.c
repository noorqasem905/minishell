/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:50:30 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/30 19:32:38 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

/*void	sort_env(char **env, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				swap_strings(&env[i], &env[j]);
			j++;
		}
		i++;
	}
}*/

/*void	env_sorted(char **env)
{
	int		i;
	int		len;
	char	**copy;

	len = ft_2dlen(env);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
	{
		ft_printf("%2env: malloc error\n");
		return;
	}
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	sort_env(copy, len);
	i = 0;
	while (copy[i])
	{
		if (ft_strchr(copy[i], '='))
			ft_printf("%s\n", copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
}*/

