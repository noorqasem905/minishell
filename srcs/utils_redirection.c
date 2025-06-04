/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:41:22 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 22:15:26 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	element_size(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	which_redirection_char(char *temp)
{
	if (!temp && !temp[0])
		return (-1);
	temp = ft_strmchr(temp, "<>");
	if (!temp)
		return (-1);
	if (temp[0] == '<')
		return ('<');
	else if (temp[0] == '>')
		return ('>');
	return (0);
}

void	quote_remove_helper(char **str, int *save_i, int *close, int *allow)
{
	if (*allow > 0 && *allow < 5)
		no_value_of_echo(*str, save_i, allow);
	if (*close == 2)
	{
		(*str)[save_i[0]] = ' ';
		(*str)[save_i[1]] = ' ';
		*close = 0;
	}
	if (*allow > 4)
		(*allow)--;
}
