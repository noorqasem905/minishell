/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:25:20 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/31 17:08:05 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quote_condition(char **str, char *who_im_i, int save_i[3], int *close)
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

int	is_valid_after_echo(const char *str, int i)
{
	char	c;

	c = str[i + 4];
	if (c == '\0' || ft_isspace(c))
		return (1);
	return (0);
}

int	is_echo_command(const char *str, int i)
{
	if (ft_strncmp(str + i, "echo", 4) == 0 && is_valid_after_echo(str, i))
		return (1);
	return (0);
}

void	no_value_of_echo(char *str, int save_i[3], int *allow)
{
	char	**split;
	int		size;

	split = ft_split_custom_exp(str + save_i[2], '|');
	if (!split)
		return ;
	size = ft_strlen(split[0]);
	frees_split(split);
	save_i[2] += size;
	*allow = 0;
}

void	remove_qoute(char **str)
{
	char	who_im_i;
	int		save_i[3];
	int		close;
	int		allow;

	allow = 0;
	close = 0;
	who_im_i = ' ';
	save_i[0] = -1;
	save_i[1] = -1;
	save_i[2] = 0;
	while ((*str)[save_i[2]])
	{
		remove_quote_condition(str, &who_im_i, save_i, &close);
		if (is_echo_command(*str, save_i[2]) && allow < 1)
			allow = 8;
		if (allow > 0 && allow < 5)
			no_value_of_echo(*str, save_i, &allow);
		if (close == 2)
		{
			(*str)[save_i[0]] = ' ';
			(*str)[save_i[1]] = ' ';
			close = 0;
		}
		if (allow > 4)
			allow--;
		save_i[2]++;
	}
}
