/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:10:19 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/12 18:19:00 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	robo_cd_access(char **dir, char **temp)
{
	if ((*dir) && access((*dir), F_OK) == 0)
	{
		if (chdir((*dir)) == -1)
		{
			write(1, "No file named this\n", 20);
			if ((*dir) != temp[1])
				free((*dir));
			return (-1);
		}
		if ((*dir) != temp[1])
		{
			write(1, "No file named this\n", 20);
			free((*dir));
		}
		return (-1);
	}
	else
		write(1, "No file named this\n", 20);
	return (0);
}

int	handle_space_infile(char ***temp, char **dir)
{
	int		start;
	int		end;

	*dir = NULL;
	if ((*temp)[1] && ((*temp)[1][0] == '"' || (*temp)[1][0] == '\''))
	{
		start = 1;
		end = start;
		if (merge_quoted_tokens(temp, dir, start, &end))
			return (-1);
	}
	else if ((*temp)[1])
		*dir = (*temp)[1];
	else
		*dir = NULL;
	return (0);
}

void	robo_cd(char **temp, t_cmd **cmd)
{
	char	*dir;

	if (handle_cd_slash(temp[1]) == -1)
		return ;
	if (handle_cd_dup_dot(temp[1], cmd) == -1)
		return ;
	if (handle_space_infile(&temp, &dir) == -1)
		return ;
	if (robo_cd_access(&dir, temp))
		return ;
	if (dir != temp[1] && dir != NULL)
	{
		write(1, "No file named this\n", 20);
		free(dir);
	}
	if (chdir(temp[1]) == -1)
		return ;
}
