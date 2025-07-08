/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:03:25 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/08 19:35:06 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	space_history(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_pipe_error(char *input, t_cmd **cmd)
{
	if (check_no_pipe(input) && check_pipe_input(input) == -1)
	{
		ft_printf("%2syntax haah error near unexpected token `|`\n");
		(*cmd)->exit_status = 2;
		return (-42);
	}
	return (0);
}

static int	validate_split_result(char ***temp)
{
	if (!*temp)
		return (-1);
	if (!*temp[0])
	{
		free(*temp);
		return (-42);
	}
	return (0);
}

static int	handle_save_data(t_cmd **cmd, int *flag, char ***temp)
{
	if (save_data(cmd, flag, temp) == -1 || *flag == -3 || *flag == 12)
	{
		if (*flag == -3)
			return (-3);
		return (-1);
	}
	return (0);
}

int	process_handle_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	char	*tmp;

	if (*input && space_history(*input))
		add_history(*input);
	replace_special_char(input);
	remove_qoute(input);
	tmp = remove_special_char(*input, '\x15');
	if (tmp)
		*input = tmp;
	if (check_pipe_error(*input, cmd) != 0)
		return (-42);
	*temp = ft_split_custom_exp(*input, '|');
	restore_loop_two(input);
	restore_loop_2d(temp);
	if (validate_split_result(temp) != 0)
		return (-1);
	return (handle_save_data(cmd, flag, temp));
}
