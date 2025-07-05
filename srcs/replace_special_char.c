/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_special_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:52:29 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 15:54:09 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	replace_in_quotes(char *str, int *i)
{
	if (str[*i] == '<')
		str[*i] = '\x11';
	else if (str[*i] == '>')
		str[*i] = '\x12';
	(*i)++;
}

static void	start_quote(int *in_quote, char *quote_char, char current_char)
{
	*in_quote = 1;
	*quote_char = current_char;
}

void	replace_special_char(char **str)
{
	int		i;
	int		in_quote;
	char	quote_char;

	if (!str || !(*str))
		return ;
	i = 0;
	in_quote = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			if (!in_quote)
				start_quote(&in_quote, &quote_char, (*str)[i]);
			else if ((*str)[i] == quote_char)
				in_quote = 0;
			i++;
			continue ;
		}
		if (in_quote)
			replace_in_quotes(*str, &i);
		else
			i++;
	}
}
