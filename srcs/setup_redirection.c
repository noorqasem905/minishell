/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:03:51 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 22:04:09 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_redirection(char *input, char **temp, char **temp2)
{
	char	state;
	int		mult;

	mult = check_redirection_mult(input);
	if (mult == -1)
		return (-1);
	state = ft_strmchr(input, "<>")[0];
	if (state == '<')
	{
		*temp = ft_strfchr(input, '<');
		*temp2 = ft_strchr(input, '<');
	}
	else
	{
		*temp = ft_strfchr(input, '>');
		*temp2 = ft_strchr(input, '>');
	}
	return (mult);
}
