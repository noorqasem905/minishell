/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/12 14:46:06 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_remove_helper(char **str, int *save_i, int *close, int *allow, char **result)
{
	if (*allow > 0 && *allow < 5)
		no_value_of_echo(*str, save_i, allow);
	if ((*close) == 2)
	{
		(*str)[save_i[0]] = '\x15';
		(*str)[save_i[1]] = '\x15';
		(*close) = 0;
	}
	if (*allow > 4)
		(*allow)--;
}

void	remove_quote_condition(char **str, char *who_im_i, int save_i[3],
		int *close, char **result)
{
	int	i;

	i = save_i[2];
	if ((*str)[i] == '\"' || (*str)[i] == '\'')
	{
		if (*who_im_i == '\0')
			*who_im_i = (*str)[i];
		else if ((*str)[i] != *who_im_i)
		{
			*who_im_i = (*str)[i];
			*close = 0;
		}
		if (*close == 0)
			save_i[0] = i;
		else
			save_i[1] = i;
		(*close)++;
	}
	else if (ft_isspace((*str)[i]))
		*close = 0;
}
