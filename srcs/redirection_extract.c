/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:44:37 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/19 17:45:13 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	extract_apply_short(char **temp, char **tmp, char ***redirection_split,
		char *temp4_copy)
{
	if (!temp4_copy)
	{
		redirection_check2free(temp, redirection_split);
		return (-1);
	}
	*tmp = ft_strjoin(*temp, " ");
	return (0);
}

void	setup_extra_command_2(char **split_2, char **command)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 1;
	while (j < (int)element_size(split_2))
	{
		tmp = ft_strjoin(split_2[j], " ");
		if (tmp)
		{
			tmp2 = ft_strjoin(*command, tmp);
			free(tmp);
			if (*command)
				free(*command);
			*command = tmp2;
		}
		j++;
	}
	frees_split(split_2);
}

int	setup_extra_command(char *temp5, char **command)
{
	char	**split;
	char	**split_2;
	int		i;

	split = ft_mult_split(temp5, "<>");
	if (!split)
		return (-1);
	i = 0;
	while (i < (int)element_size(split))
	{
		split_2 = ft_split(split[i], ' ');
		if (!split_2)
		{
			frees_split(split);
			return (-1);
		}
		if (split_2)
			setup_extra_command_2(split_2, command);
		i++;
	}
	frees_split(split);
	return (0);
}

int	extract_apply_short_2(char *tmp, char *temp5, char *temp4_copy,
		char **command)
{
	(*command) = ft_strjoin(tmp, temp4_copy);
	setup_extra_command(temp5, command);
	free(tmp);
	free(temp4_copy);
	if (!(*command))
		return (-1);
	return (0);
}

void	extract_apply_short_3(char **tmp, char **temp, char *temp4,
		char **command)
{
	(*tmp) = ft_strjoin(*temp, " ");
	(*command) = ft_strjoin((*tmp), temp4);
	free(*tmp);
}
