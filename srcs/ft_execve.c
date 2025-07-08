/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:03:10 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/08 17:19:45 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_validation_handle(int flag, char *m, char **result)
{
	if (m == NULL || flag < 0)
	{
		free_it_noww(result, NULL, 1);
		if (m != NULL)
			free(m);
		return (-1);
	}
	return (0);
}

static int	ft_execve_cleanup(char **result, char **paths)
{
	if (paths)
		frees_split(paths);
	free_it_noww(result, NULL, 1);
	return (-1);
}

static int	ft_execve_execute(char *m, char **result, t_cmd **cmd)
{
	if (execve(m, result, (*cmd)->env) == -1)
	{
		free_it_noww(result, m, 1);
		return (-1);
	}
	free_it_noww(result, m, 0);
	return (0);
}

int	ft_execve(char *file, t_cmd **cmd)
{
	char	**result;
	char	**paths;
	int		flag;
	char	*m;

	flag = ft_setup_execve(file, &result, (*cmd)->env, &paths);
	if (flag == -1)
		return (-1);
	if (!result || !result[0] || !*result[0])
		return (ft_execve_cleanup(result, paths));
	(*cmd)->lock = flag;
	flag = check_validation(paths, result, &m, cmd);
	if (check_validation_handle(flag, m, result) < 0)
		return (-1);
	return (ft_execve_execute(m, result, cmd));
}

