/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:20:32 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/28 16:13:04 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_var_exist(char *name, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], name, ft_strlen(name)) == 0
			&& cmd->env[i][ft_strlen(name)] == '='
			/* || cmd->env[i][ft_strlen(name) - 1] == '\0' */)
			return (1);
		i++;
	}
	return (0);
}

static int	is_matching_var(char *env_entry, char *name)
{
	return (ft_strncmp(env_entry, name, ft_strlen(name)) == 0
		&& (env_entry[ft_strlen(name)] == '='
			|| env_entry[ft_strlen(name)] == '\0'));
}

static char	**copy_env_without_var(char **env, char *name)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	i = 0;
	j = 0;
	len = 0;
	while (env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (!is_matching_var(env[i], name))
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	robo_unset(char *name, t_cmd **cmd)
{
	char	**new_env;

	if (ft_strcmp(name, "PATH") == 0 || ft_strcmp(name, "HOME") == 0)
		(*cmd)->flag = 1;
	if (!is_valid(name))
	{
		ft_printf("unset: `%s`: not a valid identifier\n", name);
		return ;
	}
	if (!is_var_exist(name, (*cmd)))
		return ;
	new_env = copy_env_without_var((*cmd)->env, name);
	if (!new_env)
		return ;
	frees_split((*cmd)->env);
	(*cmd)->env = new_env;
	save_export_to_expo(cmd);
}

/* void	robo_unset(char *name, t_cmd **cmd)
{
	int		i;
	int		j;
	int		len;
	int		lenn;
	char	**new_env;
	char	**new_expo;

	if (ft_strcmp(name, "PATH") == 0 || ft_strcmp(name, "HOME") == 0)
		(*cmd)->flag = 1;
	if (!is_valid(name))
	{
		ft_printf("unset: `%s`: not a valid identifier\n", name);
		return ;
	}
	if (!is_var_exist(name, (*cmd)))
		return ;
	len = 0;
	while ((*cmd)->env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*cmd)->env[i])
	{
		if (!(ft_strncmp((*cmd)->env[i], name, ft_strlen(name)) == 0 &&
			((*cmd)->env[i][ft_strlen(name)] == '='
				|| (*cmd)->env[i][ft_strlen(name)] == '\0')))
		{
			new_env[j++] = ft_strdup((*cmd)->env[i]);
		}
		i++;
	}
	new_env[j] = NULL;
	frees_split((*cmd)->env);
	(*cmd)->env = new_env;
	save_export_to_expo((cmd));
}
 */