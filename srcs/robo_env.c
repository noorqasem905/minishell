/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:42:58 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/22 17:32:16 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_cmd *cmd)
{
	char	*eq;
	int		i;

	i = 0;
	while (cmd->env[i])
	{
		eq = ft_strchr(cmd->env[i], '=');
		if (eq && *(eq + 1) != '\0')
			ft_printf("%s\n", cmd->env[i]);
		i++;
	}
}
