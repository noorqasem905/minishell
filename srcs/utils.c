/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:14:40 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/30 19:18:33 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	word_lenn(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

void	frees_newsplit(char **root)
{
	int	i;

	i = 0;
	while (root[i])
	{
		free(root[i]);
		i++;
	}
	free(root);
	root = NULL;
}

int	is_valid(char *name)
{
	int	i;

	if (!name || name[0] == ' ' || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_quotes(char **s, int *flag)
{
	if (**s == '\"')
	{
		*flag = !(*flag);
		(*s)++;
		return (1);
	}
	return (0);
}

void	ski_delimiters(char **s, char c)
{
	while (*s && **s == c)
		(*s)++;
}
