/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:44:05 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/10 18:41:25 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*allocate_result(char *str, char special_char)
{
	int		count;
	char	*result;

	if (!str)
		return (NULL);
	count = count_special_char(str, special_char);
	if (count == 0)
		return (NULL);
	result = malloc(strlen(str) + 1 - count);
	if (!result)
		return (NULL);
	return (result);
}

int	count_special_char(char *str, char special_char)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == special_char)
			count++;
		i++;
	}
	return (count);
}

char	*remove_special_char(char *str, char special_char)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = allocate_result(str, special_char);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != special_char)
			result[j++] = str[i];
		i++;
	}
	if (j == 0)
	{
		free(str);
		free(result);
		return (NULL);
	}
	free(str);
	result[j] = '\0';
	return (result);
}

void	signal_main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
