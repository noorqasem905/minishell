/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:59:00 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/08 19:46:35 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_loop_two(char **str)
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

char	*restore_special_str(const char *str)
{
	size_t	len;
	char	*restr;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	len = strlen(str);
	restr = (char *)malloc(len + 1);
	if (!restr)
		return (NULL);
	while (i < len)
	{
		if (str[i] == '\x11')
			restr[i] = '<';
		else if (str[i] == '\x12')
			restr[i] = '>';
		else if (str[i] == '\x13')
			restr[i] = '|';
		else
			restr[i] = str[i];
		i++;
	}
	restr[len] = '\0';
	return (restr);
}
