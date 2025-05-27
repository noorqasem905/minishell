/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:01:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 22:02:02 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exp	*init_export(int count)
{
	t_exp	*export;

	export = malloc(sizeof(t_exp));
	if (!export)
		return (NULL);
	export->name = ft_calloc(count + 1, sizeof(char *));
	export->value = ft_calloc(count + 1, sizeof(char *));
	if (!export->name || !export->value)
	{
		if (export->name)
			free(export->name);
		if (export->value)
			free(export->value);
		free(export);
		return (NULL);
	}
	return (export);
}
