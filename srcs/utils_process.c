/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:35:24 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/10 17:57:49 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	space_history(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

void	restore_loop(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\x13')
			(*str)[i] = '|';
		i++;
	}
}

void	restore_loop_2d(char ***str)
{
	int	i;
	int	j;

	i = 0;
	while ((*str)[i])
	{
		j = 0;
		while ((*str)[i][j])
		{
			if ((*str)[i][j] == '\x13')
				(*str)[i][j] = '|';
			j++;
		}
		i++;
	}
}

int	process_input_leaks(t_cmd **cmd, int ret)
{
	if (ret < 0)
		return (ret);
	if ((*cmd)->here_doc->file_loc)
		handle_here_doc_nolink(cmd);
	if ((*cmd)->here_doc->pryority)
		free((*cmd)->here_doc->pryority);
	return (0);
}

int	save_data(t_cmd **cmd, int *flag, char ***temp)
{
	int	size;
	int	iterator;

	*flag = 0;
	if (*temp == NULL)
	{
		perror("ft_split");
		return (-1);
	}
	size = ft_2dlen(*temp);
	if (size == 0)
		return (*flag = -3);
	(*cmd)->word = NULL;
	iterator = -1;
	while (++iterator < size)
	{
		if ((*temp)[iterator] != NULL)
		{
			insertend(&((*cmd)->word), (*temp)[iterator], flag);
			if (*flag == 12)
				break ;
		}
	}
	return (0);
}
