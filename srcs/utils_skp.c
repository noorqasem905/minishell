/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_skp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:02:01 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/10 14:24:56 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirection(char *str, int *i, int *enter)
{
	char	c;
	int		k;

	*enter = 1;
	c = str[*i];
	if (is_invalid_redirect(str, *i))
		return (1);
	if (str[*i + 1] && str[*i + 1] == c)
		(*i)++;
	k = *i + 1;
	while (str[k] && ft_isspace(str[k]))
		k++;
	if (!str[k] || str[k] == '<' || str[k] == '>')
		return (1);
	return (0);
}

int	is_invalid_redirect(char *str, int i)
{
	char	a;
	char	b;
	char	c;

	a = str[i];
	b = str[i + 1];
	if (ft_strlen(str + i) == 1)
		c = '\0';
	else
		c = str[i + 2];
	if ((a == '<' || a == '>')
		&& (b == '<' || b == '>')
		&& (c == '<' || c == '>'))
		return (1);
	if ((a == '<' && b == '>') || (a == '>' && b == '<'))
		return (1);
	return (0);
}

int	handle_ret_export(char *str, t_cmd **cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == ' ' && str[i + 1] == '=')
		{
			(*cmd)->exit_status = 1;
			write(2, "export: `=`:not a valid identifier\n", 36);
			return (-1);
		}
		i++;
	}
	return (0);
}
