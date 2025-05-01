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


void	swap_strings(char **a, char **b)
{
	char	*temp;
    
    temp = *a;
	*a = *b;
	*b = temp;
}
void	sort_env(char **env, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap_strings(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

