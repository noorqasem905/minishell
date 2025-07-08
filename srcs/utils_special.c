/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:14:41 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/08 19:15:07 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_special_char(char *str, char special_char)
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

static int	should_return_null(char *str, int count)
{
	if (!str || count == 0)
		return (1);
	return (0);
}

static void	copy_except_special(char *src, char *dest, char special, int *j)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] != special)
			dest[(*j)++] = src[i];
		i++;
	}
}

char	*remove_special_char(char *str, char special_char)
{
	char	*result;
	int		j;
	int		count;

	j = 0;
	count = count_special_char(str, special_char);
	if (should_return_null(str, count))
		return (NULL);
	result = malloc(ft_strlen(str) + 1 - count);
	if (!result)
		return (NULL);
	copy_except_special(str, result, special_char, &j);
	if (j == 0)
	{
		if (*str)
			free(str);
		free(result);
		return (NULL);
	}
	free(str);
	result[j] = '\0';
	return (result);
}
