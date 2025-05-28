/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:58:09 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/28 18:04:44 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_path(char **ev)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=/", 6) == 0)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (ev[i] == NULL)
		return (-1);
	if (flag == 0)
		return (-1);
	return (i);
}

void	no_space(int *l, char **m, char **o)
{
	*l = -1;
	*o = "/";
	*m = NULL;
}

int	handle_ecv_slash(char *result, char **m, char **paths)
{
	if (result && ft_strncmp(result, "/", 1) == 0)
	{
		if (access(result, F_OK | X_OK) == 0 && ft_strcmp(result, "/") != 0)
		{
			*m = ft_strdup(result);
			return (5);
		}
		else
		{
			free_it_noww(paths, NULL, 0);
			return (-6);
		}
	}
	return (0);
}

int	check_validation(char **paths, char **result, char **m)
{
	int	ret;

	*m = NULL;
	if (!paths)
	{
		free_it_noww(paths, NULL, 1);
		return (-1);
	}
	if (result[0] && ft_strncmp(result[0], "./", 2) == 0)
	{
		if (access(result[0], X_OK) == -1 || ft_strcmp(result[0], "./") == 0)
		{
			free_it_noww(paths, NULL, 0);
			perror("Error: File is not executable or doesn't exist");
			return (1);
		}
		*m = ft_strdup(result[0]);
		return (4);
	}
	ret = handle_ecv_slash(result[0], m, paths);
	if (ret == 5 || ret == -6)
		return (ret);
	*m = check_access(paths, result);
	return (0);
}

void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n", str, split[i]);
		i++;
	}
}
