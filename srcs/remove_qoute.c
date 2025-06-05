/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:25:20 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 15:53:10 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!str[i] || !str[i + 1] || !str[i + 2] || !str[i + 3])
		return (0);
	if (ft_strncmp(str + i, "echo", 4) == 0 && is_valid_after_echo(str, i))
		return (1);
	return (0);
}

void	no_value_of_echo(char *str, int save_i[3], int *allow)
{
	char	**split;
	int		size;
	int		len;

	len = ft_strlen(str + save_i[2]);
	if (len <= 0)
		return ;
	split = ft_split_custom_exp(str + save_i[2], '|');
	if (!split)
		return ;
	size = ft_strlen(split[0]);
	frees_split(split);
	if (save_i[2] + size > len)
		size = len - save_i[2];
	save_i[2] += size;
	*allow = 0;
}

static void	init_value(int save_i[3], char *who_im_i, int *allow, int *close)
{
	*allow = 0;
	*close = 0;
	*who_im_i = ' ';
	save_i[0] = -1;
	save_i[1] = -1;
	save_i[2] = 0;
}

void	remove_qoute(char **str)
{
	char	who_im_i;
	int		save_i[3];
	int		close;
	int		allow;

	init_value(save_i, &who_im_i, &allow, &close);
	while ((*str) && (*str)[save_i[2]])
	{
		if (is_echo_command(*str, save_i[2]))
		{
			save_i[2] += 4;
			while ((*str)[save_i[2]] && ft_isspace((*str)[save_i[2]]))
				save_i[2]++;
			while ((*str)[save_i[2]] && (*str)[save_i[2]] != '|')
				save_i[2]++;
			continue ;
		}
		remove_quote_condition(str, &who_im_i, save_i, &close);
		quote_remove_helper(str, save_i, &close, &allow);
		save_i[2]++;
	}
}
