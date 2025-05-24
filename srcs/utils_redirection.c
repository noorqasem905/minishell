/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:41:22 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/24 18:25:47 by nqasem           ###   ########.fr       */
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
