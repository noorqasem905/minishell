/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:39:45 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/12 20:41:41 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	save_data(t_cmd **cmd, int *flag, char ***temp)
{
	int	size;
	int	iterator;

	*flag = 0;
	if (*temp == NULL)
	{
		perror("ft_split");
		return (-1);
	}
	size = ft_2dlen(*temp);
	if (size == 0)
		return (*flag = -3);
	(*cmd)->word = NULL;
	iterator = -1;
	while (++iterator < size)
	{
		if ((*temp)[iterator] != NULL)
		{
			insertend(&((*cmd)->word), (*temp)[iterator], flag);
			if (*flag == 12)
				break ;
		}
	}
	return (0);
}

static int	count_special_char(char *str, char special_char)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == special_char)
			count++;
		i++;
	}
	return (count);
}

char	*remove_special_char(char *str, char special_char)
{
	char	*result;
	int		i = 0;
	int		j = 0;
	int		count;

	if (!str)
		return (NULL);

	count = count_special_char(str, special_char);
	if (count == 0)
		return (NULL);
	result = malloc(ft_strlen(str) + 1 - count);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i] != special_char)
			result[j++] = str[i];
		i++;
	}
	if (j == 0)
	{
		if (*str)
			free(str);
		free(result);
		return (NULL);
	}
	free(str);
	result[j] = '\0';
	return (result);
}

static int space_history(char *input)
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

int	process_handle_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	char *tmp;
	if (*input && space_history(*input))
		add_history(*input);
	remove_qoute(input);
	tmp = remove_special_char(*input, '\x15');
	if (tmp)
		*input = tmp;
	if (check_no_pipe(*input) && check_pipe_input(*input) == -1)
	{
		ft_printf("%2syntax error near unexpected token `|`\n");
		(*cmd)->exit_status = 2;
		return (-42);
	}
	replace_special_char(input);
	*temp = ft_split_custom_exp(*input, '|');
	if (!*temp)
		return (-1);
	if (!*temp[0])
	{
		free(*temp);
		return (-42);
	}
	if (save_data(cmd, flag, temp) == -1 || *flag == -3 || *flag == 12)
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

	ret_of_searching = 0;
	if (!(*split) || !*(*split))
	{
		if ((*split))
			free((*split));
		free(*input);
		return (-3);
	}
	*t = expander_input(cmd, (*cmd)->word);
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
	char	**split;
	char	*t;
	int		ret_of_searching;

	ret_of_searching = process_handle_input(cmd, flag, temp, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	(*cmd)->input = *input;
	if (searching_comand(*temp) == -1)
		return (-1);
	split = ft_split((*temp)[0], ' ');
	ret_of_searching = process_set_input(cmd, &t, &split, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	if (searching_comand(*temp) == -13)
		return (-13);
	(*cmd)->input = *input;
	ret_of_searching = execution(cmd);
	ret_of_searching = exitting_handle(ret_of_searching, cmd, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	ret_of_searching = process_input_leaks(cmd, ret_of_searching);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	return (0);
}
