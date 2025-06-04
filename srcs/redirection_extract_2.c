/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_extract_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:45:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 01:33:02 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_data_extr_apy_redir(int *which, char *temp2, char **temp4,
		char **redirection_split)
{
	char	*temp4_raw;

	*which = which_redirection_char(temp2 + 1);
	temp4_raw = ft_strmchr(temp2, "<>");
	*temp4 = get_redirection_command(temp4_raw, redirection_split, 0);
}

static int	free_and_ret(char *temp, int ret_value, char *str)
{
	if (str)
		ft_printf("%2%s", str);
	free(temp);
	return (ret_value);
}

int	extract_and_apply_redirection(char **temp, char *temp2,
		char ***redirection_split, char **command)
{
	char	*temp4_copy;
	char	*temp4;
	char	*temp5;
	char	*th;
	int		which;

	set_data_extr_apy_redir(&which, temp2, &temp4, *redirection_split);
	if (which > 0)
	{
		th = ft_strfchr(temp2 + 1, which);
		temp5 = ft_strmchr(temp4, "<>");
		if (handle_redirection_segment(redirection_split, temp, &temp4, th) < 0)
			return (free_and_ret(temp5, -1, NULL));
		temp4_copy = ft_strdup(temp4);
		free(th);
		if (extract_apply_short(temp, &th, redirection_split, temp4_copy) < 0)
			return (free_and_ret(temp5, -1, NULL));
		if (extract_apply_short_2(th, temp5, temp4_copy, command) < 0)
			return (redirection_check2free(temp, redirection_split));
	}
	else
		extract_apply_short_3(&th, temp, temp4, command);
	return (0);
}


// here you can add sections to add echo value to command with includes ">" or something like that
// here you can add sections to add echo value to command with includes "<<" or something like that