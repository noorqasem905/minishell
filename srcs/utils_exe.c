/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:39:23 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/08 19:41:40 by aalquraa         ###   ########.fr       */
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

static int	handle_split_error(char ***result)
{
	perror("Error splitting file");
	*result = NULL;
	return (-1);
}

static int	handle_path_failure(char ***result)
{
	frees_split(*result);
	return (-1);
}

static int	handle_paths_split_fail(char ***result)
{
	free_it_noww(*result, NULL, 1);
	return (-1);
}

int	ft_setup_execve(char *file, char ***result, char **ev, char ***paths)
{
	int	get;

	if (!file || !*file)
		return (-1);
	*result = ft_split(file, ' ');
	if (!*result)
		return (handle_split_error(result));
	if ((*result)[0] && (!ft_strncmp((*result)[0], "./", 2)
			|| !ft_strncmp((*result)[0], "/", 1)))
		return (3);
	get = get_path(ev);
	if (get < 0)
		return (handle_path_failure(result));
	*paths = ft_split(ev[get] + 5, ':');
	if (!*paths)
		return (handle_paths_split_fail(result));
	return (0);
}
