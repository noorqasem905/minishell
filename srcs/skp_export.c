/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:25:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/10 14:25:11 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	append_char_export(char **tmp, char *ch)
{
	char	*new;

	new = ft_strjoin(*tmp, ch);
	if (!new)
		return (1);
	free(*tmp);
	*tmp = new;
	return (0);
}

static void	skip_redirect_word(char *str, int *i)
{
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
}

static int	handle_redirection_case(char **str, char **tmp, int *enter, int *i)
{
	if (handle_redirection((*str), i, enter))
	{
		free(*tmp);
		return (-1);
	}
	return (0);
}

static int	handle_append_or_skip(char **str, char **tmp, int *enter, int *i)
{
	char	ch[2];

	if (*enter == 0)
	{
		ch[0] = (*str)[*i];
		ch[1] = '\0';
		if (append_char_export(tmp, ch))
		{
			free(*tmp);
			return (-1);
		}
	}
	else if (!ft_isspace((*str)[*i]))
	{
		*enter = 0;
		skip_redirect_word((*str), i);
		return (1);
	}
	return (0);
}

int	loop_skip(char **str, char **tmp, int *enter, int *i)
{
	if (((*str)[*i] == '<' || (*str)[*i] == '>') && *enter == 0)
		return (handle_redirection_case(str, tmp, enter, i));
	return (handle_append_or_skip(str, tmp, enter, i));
}
