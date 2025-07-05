/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:58:09 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/05 12:28:59 by aalquraa         ###   ########.fr       */
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

int	handle_ecv_slash(char *result, char **m, char **paths, t_cmd **cmd)
{
	if (result && ft_strncmp(result, "/", 1) == 0)
	{
		if (access(result, F_OK | X_OK) == 0 && ft_strcmp(result, "/") != 0)
		{
			if ((*cmd)->lock != 3 && paths)
				free_it_noww(paths, NULL, 0);
			*m = ft_strdup(result);
			return (5);
		}
		else
		{
			if ((*cmd)->lock != 3 && *paths)
				free_it_noww(paths, NULL, 0);
			return (-6);
		}
		if ((*cmd)->lock != 3 && *paths)
			free_it_noww(paths, NULL, 0);
	}
	return (0);
}

/*int	shell_level_increment(t_cmd **cmd, int flag)
{
	int		shlvl_idx;
	char	*shlvl_val;
	int		new_shlvl;
	char	*num;
	char	*export_str;

	shlvl_idx = get_env_j((*cmd)->env, "SHLVL");
	if (shlvl_idx != -1)
	{
		shlvl_val = ft_strchr((*cmd)->env[shlvl_idx], '=');
		if (shlvl_val)
			new_shlvl = ft_atoi(shlvl_val + 1) + (1 * (flag));
	}
	else
		new_shlvl = 1;
	num = ft_itoa(new_shlvl);
	export_str = ft_strjoin("export SHLVL=", num);
	ft_export(export_str, cmd);
	free(num);
	free(export_str);
	return (0);
}*/

int	check_validation(char **paths, char **result, char **m, t_cmd **cmd)
{
	int		ret;
	char	*cwd;
	char	*num;

	*m = NULL;
	if (result[0] && ft_strncmp(result[0], "./", 2) == 0)
	{
		if (access(result[0], X_OK) == -1 || ft_strcmp(result[0], "./") == 0)
		{
			if ((*cmd)->lock != 3 && *paths)
				free_it_noww(paths, NULL, 0);
			return (1);
		}
		if ((*cmd)->lock != 3 && *paths)
			free_it_noww(paths, NULL, 0);
		*m = ft_strdup(result[0]);
		/*if (ft_strcmp(*m, "./minishell") == 0)
			shell_level_increment(cmd, 1);*/
		return (4);
	}
	ret = handle_ecv_slash(result[0], m, paths, cmd);
	if (ret == 5 || ret == -6)
		return (ret);
	*m = check_access(paths, result);
	return (0);
}
