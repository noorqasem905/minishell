/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:28 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/10 13:49:54 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	rem_complete(char ***result, int i_k_j[3])
{
	(*result)[i_k_j[0]][i_k_j[1]++]
		= (*result)[i_k_j[0]][i_k_j[2]];
}

int	remove_quotues(char ***result)
{
	int		i_k_j[3];
	char	quote;

	i_k_j[0] = -1;
	while ((*result)[++i_k_j[0]])
	{
		i_k_j[2] = 0;
		i_k_j[1] = 0;
		quote = 0;
		while ((*result)[i_k_j[0]][i_k_j[2]])
		{
			if (!quote && ((*result)[i_k_j[0]][i_k_j[2]] == '\''
				|| (*result)[i_k_j[0]][i_k_j[2]] == '\"'))
				quote = (*result)[i_k_j[0]][i_k_j[2]];
			else if (quote && (*result)[i_k_j[0]][i_k_j[2]] == quote)
				quote = 0;
			else
				rem_complete(result, i_k_j);
			i_k_j[2]++;
		}
		(*result)[i_k_j[0]][i_k_j[1]] = '\0';
		if (quote)
			return (free_err_ret(NULL, NULL, (*result), -1));
	}
	return (0);
}

int	handle_ret_export(char *str, t_cmd **cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == ' ' && str[i + 1] == '=')
		{
			(*cmd)->exit_status = 1;
			write(2, "export: `=`:not a valid identifier\n", 36);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*skp(char *str)
{
	int		i;
	int		ret;
	int		enter;
	char	*tmp;

	i = 0;
	ret = 0;
	enter = 0;
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		ret = loop_skip(&str, &tmp, &enter, &i);
		if (ret == -1)
			return (NULL);
		else if (ret == 1)
			continue ;
		i++;
	}
	if (enter == 1)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
