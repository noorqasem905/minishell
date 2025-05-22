/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:26:37 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/22 20:02:33 by aalquraa         ###   ########.fr       */
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
