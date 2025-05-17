/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:14:59 by nqasem            #+#             */
/*   Updated: 2025/04/10 14:42:50 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_it_now(char **s, char *s2, int emassage)
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
		perror("Error");
}

int		handle_ecv_slash(char *result, char **m, char **paths)
{
	if (result && ft_strncmp(result, "/", 1) == 0)
	{
		if (access(result, F_OK | X_OK) == 0)
		{
			*m = ft_strdup(result);
			return (5);
		}
		else
		{
			free_it_now(paths, NULL, 0);
			return (-6);
		}
	}
	return (0);
}

int	check_validation(char **paths, char **result, char **m)
{
	int ret;

	*m = NULL;
	if (!paths)
	{
		free_it_now(paths, NULL, 1);
		return (-1);
	}
	if (result[0] && ft_strncmp(result[0], "./", 2) == 0)
	{
		if (access(result[0], X_OK) == -1)
		{
			free_it_now(paths, NULL, 0);
			perror("Error: File is not executable or doesn't exist");
			return (1);
		}
		*m = ft_strdup(result[0]);
		return (4);
	}
	ret = handle_ecv_slash(result[0], m, paths);
	if(ret == 5 || ret == -6)
		return (ret);
	*m = check_access(paths, result);
	return (0);
}

int	get_path(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=/", 6) == 0)
			break ;
		i++;
	}
	return (i);
}

static void	no_space(int *l, char **m, char **o)
{
	*l = -1;
	*o = "/";
	*m = NULL;
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
	free_it_now(paths, p, 0);
	return (m);
}

int		ft_setup_execve(char *file, char ***result, char **ev, char ***paths)
{
	if (!file)
		return (-1);
	*result = ft_split(file, ' ');
	if (!*result)
	{
		perror("Error splitting file");
 		return (-1);
	}
	*paths = ft_split(ev[get_path(ev)] + 5, ':');
	if (!*paths)
	{
		free_it_now(*result, NULL, 1);
		return (-1);
	}
	return (0);
}

int		check_validation_handle(int flag, char *m, char **result)
{
	if (m == NULL || flag < 0)
	{
		free_it_now(result, NULL, 1);
		if (m != NULL)
			free(m);
		return (-1);
	}
	return (0);
}

int		ft_execve(char *file, char **ev)
{
	char	**result;
	char	**paths;
	int		flag;
	char	*m;

	if(ft_setup_execve(file, &result, ev, &paths) == -1)
		return (-1);
    if (!result || !result[0] || !*result[0]) 
	{
		if (paths)
			frees_split(paths);
        free_it_now(result, NULL, 1);
        return (-1);
    }
	flag = check_validation(paths, result, &m);
	if (check_validation_handle(flag, m	, result) < 0)
		return (-1);
	if (execve(m, result, ev) == -1)
	{
		perror("Error executing command");
		free_it_now(result, m, 1);
		return (-1);
	}
	free_it_now(result, m, 0);
	return (0);
}
