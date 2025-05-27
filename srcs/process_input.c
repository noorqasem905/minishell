/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:39:45 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 18:45:14 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_handle_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	if (*input)
		add_history(*input);
	if (check_no_pipe(*input) && check_pipe_input(*input) == -1)
	{
		ft_printf("%2syntax error near unexpected token `|`\n");
		(*cmd)->exit_status = 2;
		return (-42);
	}
	*temp = ft_split(*input, '|');
	if (!*temp)
		return (-1);
	if (!*temp[0])
	{
		free(*temp);
		return (-42);
	}
	if (save_data(NULL, cmd, flag, temp) == -1 || *flag == -3 || *flag == 12)
	{
		if (*flag == -3)
			return (-3);
		return (-1);
	}
	return (0);
}

int	process_set_input(t_cmd **cmd, char **t, char ***split, char **input)
{
	int	ret_of_searching;

	if (!(*split) || !*(*split))
	{
		if ((*split))
			free((*split));
		free(*input);
		return (-3);
	}
	*t = expander_input(cmd);
	if (!t)
		return (-1);
	ret_of_searching = searching_bulidin((*split), cmd, (*t), input);
	if (ret_of_searching < 0)
	{
		free(*t);
		frees_split((*split));
		return (ret_of_searching);
	}
	free(*t);
	frees_split((*split));
	return (ret_of_searching);
}

int	process_input_leaks(t_cmd **cmd, int ret)
{
	if (ret < 0)
		return (ret);
	if ((*cmd)->here_doc->file_loc)
		handle_here_doc_nolink(cmd);
	if ((*cmd)->here_doc->pryority)
		free((*cmd)->here_doc->pryority);
	return (0);
}

int	process_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	t_list	*current;
	char	**split;
	char	*t;
	int		ret_of_searching;

	ret_of_searching = process_handle_input(cmd, flag, temp, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	if (searching_comand(input, *temp) == -1)
		return (-1);
	split = ft_split((*temp)[0], ' ');
	ret_of_searching = process_set_input(cmd, &t, &split, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	if (searching_comand(input, *temp) == -13)
		return (-13);
	expand_cmds(cmd, *input);
	ret_of_searching = execution(cmd);
	ret_of_searching = exitting_handle(ret_of_searching, cmd, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	ret_of_searching = process_input_leaks(cmd, ret_of_searching);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	return (0);
}
