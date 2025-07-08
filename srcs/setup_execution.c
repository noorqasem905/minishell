/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:14:59 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/08 19:44:53 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_access(char **paths, char **result)
{
	int		l;
	char	*full_path;
	char	*m;
	char	*o;
	char	*p;

	no_space(&l, &m, &o);
	p = ft_strjoin(o, result[0]);
	while (paths[++l])
	{
		full_path = ft_strjoin(paths[l], p);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			m = ft_strdup(full_path);
			free(full_path);
			break ;
		}
		free(full_path);
	}
	free_it_noww(paths, p, 0);
	return (m);
}

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

int	ft_execve_handle_empty(char **paths, char **result)
{
	if (paths)
		frees_split(paths);
	free_it_noww(result, NULL, 1);
	return (-1);
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
		return (ft_execve_handle_empty(paths, result));
	(*cmd)->lock = flag;
	flag = check_validation(paths, result, &m, cmd);
	if (check_validation_handle(flag, m, result) < 0)
		return (-1);
	if (execve(m, result, (*cmd)->env) == -1)
	{
		free_it_noww(result, m, 1);
		return (-1);
	}
	free_it_noww(result, m, 0);
	return (0);
}
