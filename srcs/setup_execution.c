/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:14:59 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 17:59:53 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_it_noww(char **s, char *s2, int emassage)
{
	int	n;

	n = 0;
	if (s2 != NULL)
	{
		free(s2);
		s2 = NULL;
	}
	while (s[n])
	{
		free(s[n]);
		n++;
	}
	if (s)
	{
		free(s);
		s = NULL;
	}
	if (emassage || emassage == -1)
		ft_printf("%2");
}

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

int	ft_setup_execve(char *file, char ***result, char **ev, char ***paths)
{
	int		get;

	if (!file || !*file)
		return (-1);
	*result = ft_split(file, ' ');
	if (!*result)
	{
		perror("Error splitting file");
		return (-1);
	}
	get = get_path(ev);
	if (get < 0)
	{
		frees_split(*result);
		return (-1);
	}
	*paths = ft_split(ev[get] + 5, ':');
	if (!*paths)
	{
		free_it_noww(*result, NULL, 1);
		return (-1);
	}
	return (0);
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

int	ft_execve(char *file, t_cmd **cmd)
{
	char	**result;
	char	**paths;
	int		flag;
	char	*m;

	if (ft_setup_execve(file, &result, (*cmd)->env, &paths) == -1)
		return (-1);
	if (!result || !result[0] || !*result[0])
	{
		if (paths)
			frees_split(paths);
		free_it_noww(result, NULL, 1);
		return (-1);
	}
	flag = check_validation(paths, result, &m);
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
