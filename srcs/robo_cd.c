/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:10:19 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/30 12:07:19 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_target_dir(char **split, t_cmd **cmd)
{
	char	*home;

	if (ft_strcmp(split[0], "cd") == 0 && !split[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("%2cd: HOME not set\n");
			(*cmd)->exit_status = 1;
			return (NULL);
		}
		return (home);
	}
	if (split[2])
	{
		ft_printf("%2cd: too many arguments\n");
		(*cmd)->exit_status = 1;
		return (NULL);
	}
	return (split[1]);
}

static void	update_paths(char *old, char *new, t_cmd **cmd)
{
	char	*tmp;
	char	*join;

	tmp = ft_strjoin("export OLDPWD=\"", old);
	join = ft_strjoin(tmp, "\"");
	free(tmp);
	ft_export(join, cmd);
	free(join);
	tmp = ft_strjoin("export PWD=\"", new);
	join = ft_strjoin(tmp, "\"");
	free(tmp);
	ft_export(join, cmd);
	free(join);
}

void	robo_cd(char **split, t_cmd **cmd)
{
	char	*old_path;
	char	*new_path;
	char	*dir;

	dir = get_target_dir(split, cmd);
	if (!dir)
		return ;
	old_path = getcwd(NULL, 0);
	if (chdir(dir) != 0)
	{
		perror("cd");
		(*cmd)->exit_status = 1;
		free(old_path);
		return ;
	}
	new_path = getcwd(NULL, 0);
	update_paths(old_path, new_path, cmd);
	free(old_path);
	free(new_path);
	(*cmd)->exit_status = 0;
}
