/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_export_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:56:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/01 01:16:49 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_count_custom(char const *s, char c)
{
	int		i;
	int		flag;
	char	quote_char;

	i = 0;
	flag = 0;
	quote_char = 0;
	while (*s)
	{
		skip_delimiters(&s, c);
		if (*s)
			i++;
		skip_word(&s, c, &flag, &quote_char);
	}
	return (i);
}

size_t	word_len_custom(char *s, char c, int *flag, char *quote_char)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c || *flag))
	{
		if (*flag && s[i] == *quote_char)
		{
			*flag = 0;
			i++;
			continue ;
		}
		if (!*flag && (s[i] == '\'' || s[i] == '\"'))
		{
			*flag = 1;
			*quote_char = s[i];
			i++;
			continue ;
		}
		i++;
	}
	return (i);
}
