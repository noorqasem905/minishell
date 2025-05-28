/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:25:20 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/28 18:56:28 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_qoute_condition(char **str, char *who_im_i, int save_i[3],
		int *close)
{
	int	i;

	i = save_i[2];
	if ((*str)[i] == '\"' || (*str)[i] == '\'')
	{
		if ((*who_im_i) == ' ')
			(*who_im_i) = (*str)[i];
		if ((*str)[i] == '\"' != (*who_im_i) && (*who_im_i) != ' ')
		{
			(*who_im_i) = (*str)[i] == '\"';
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

void	remove_qoute(char **str)
{
	char	who_im_i;
	int		save_i[3];
	int		close;
	int		i;

	i = 0;
	close = 0;
	save_i[0] = -1;
	save_i[1] = -1;
	save_i[2] = 0;
	who_im_i = ' ';
	while ((*str)[save_i[2]])
	{
		remove_qoute_condition(str, &who_im_i, save_i, &close);
		if (close == 2)
		{
			(*str)[save_i[0]] = ' ';
			(*str)[save_i[1]] = ' ';
		}
		(save_i[2])++;
	}
}
