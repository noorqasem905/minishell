/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retore_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:47:58 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/30 22:31:45 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_quotes(char *split, char ignore)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff = malloc(ft_strlen(split) + 1);
	if (!buff)
		return (NULL);
	while (split[i])
	{
		if (split[i] != ignore)
		{
			buff[j] = split[i];
			j++;
		}
		i++;
	}
	buff[j] = '\0';
	return (buff);
}

static void	update_quote_state(const char *str, int i, int *in_quote,
	char *quote_char)
{
	if (!*in_quote)
	{
		*in_quote = 1;
		*quote_char = str[i];
	}
	else if (str[i] == *quote_char)
		*in_quote = 0;
}

static char	restore_special_char(char c)
{
	if (c == '\x11')
		return ('<');
	else if (c == '\x12')
		return ('>');
	else if (c == '\x13')
		return ('|');
	return (c);
}

static void	restore_loop(const char *str, char *res)
{
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			update_quote_state(str, i, &in_quote, &quote_char);
		if (in_quote && (str[i] == '\x11' || str[i] == '\x12' || str[i] == '\x13'))
			res[j++] = restore_special_char(str[i]);
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
}

char	*restore_special_char_in_quotes(const char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	restore_loop(str, res);
	return (res);
}
