/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/01 14:55:52 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quote_condition(char **str, char *who_im_i, int save_i[3],
		int *close)
{
	int	i;

	i = save_i[2];
	if ((*str)[i] == '\"' || (*str)[i] == '\'')
	{
		if (*who_im_i == ' ')
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
