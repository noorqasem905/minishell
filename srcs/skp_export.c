/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:25:38 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/09 18:38:57 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell.h"
#include "../libft/libft.h"

static int	is_invalid_redirect(char *str, int i)
{
	char	a = str[i];
	char	b = str[i + 1];
	char	c = str[i + 2];

	if ((a == '<' || a == '>') &&
		(b == '<' || b == '>') &&
		(c == '<' || c == '>'))
		return (1);
	if ((a == '<' && b == '>') || (a == '>' && b == '<'))
		return (1);
	return (0);
}

static int	handle_redirection(char *str, int *i, int *enter)
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
	while (str[k] && isspace(str[k]))
		k++;
	// Error: no word after redirection
	if (!str[k] || str[k] == '<' || str[k] == '>')
		return (1);
	return (0);
}

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
	while (str[*i] && !isspace(str[*i]))
		(*i)++;
}

char	*skp(char *str)
{
	int		i;
	int		enter;
	char	*tmp;
	char	ch[2];

	i = 0;
	enter = 0;
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && enter == 0)
		{
			if (handle_redirection(str, &i, &enter))
				return (free(tmp), NULL);
		}
		else if (enter == 0)
		{
			ch[0] = str[i];
			ch[1] = '\0';
			if (append_char_export(&tmp, ch))
				return (NULL);
		}
		else if (!isspace(str[i]))
		{
			enter = 0;
			skip_redirect_word(str, &i);
			continue ;
		}
		i++;
	}
	if (enter == 1)
		return (free(tmp), NULL);
	return (tmp);
}
