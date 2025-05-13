/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/13 19:00:17 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define COLOR_CUSTOM "\x1b[38;2;42;161;179m"
#define COLOR_RESET "\x1b[0m"

static int	is_closed(char *input)
{
	int	i;
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dquote == 0)
			squote = !squote;
		else if (input[i] == '"' && squote == 0)
			dquote = !dquote;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (0);
}

int	save_data(char **input, t_cmd **cmd, int *flag, char ***temp)
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
void	print_saved_cmd(t_list *saved_cmd)
{
	t_list	*current;

	current = saved_cmd;
	while (current != NULL)
	{
		ft_printf("Command: %s\n", (char *)current->content);
		current = current->next;
	}
}

void	init_data(t_cmd **cmd)
{
	t_here_doc	*here_doc;

	here_doc = (*cmd)->here_doc;
	(*cmd)->word = NULL;
	(*cmd)->env = NULL;
	(*cmd)->pryority = NULL;
	(*cmd)->who_am_i = 0;
	(*cmd)->counter = 0;
	(*cmd)->index = 0;
	(*cmd)->here_doc->file_loc = NULL;
	(*cmd)->exit_status = 0;
	here_doc->counter = 0;
	here_doc->index = 0;
	here_doc->pryority = NULL;
	here_doc->temp = NULL;
	here_doc->fd = 0;
}
int	check_no_pipe(char *input)
{
	int	i;

	i = 0;
	ft_strchr(input, '|');
	while (input[i])
	{
		if (input[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe_input(char *input)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input)
		return (-1);
	if (input[i] && input[i] == '|' || input[ft_strlen(input) - 1] == '|')
		return (-1);
	while (input[i])
	{
		if (input[i] != '|' && input[i] != ' ')
			pipe_count = 0;
		else if (input[i] == '|')
			pipe_count++;
		if (pipe_count > 1)
			return (-1);
		i++;
	}
	if (pipe_count > 0)
		return (-1);
	return (0);
}
void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n", str, split[i]);
		i++;
	}
}
int	process_input(t_cmd **cmd, int *flag, char ***temp, char **input,
		char **robo_env)
{
	t_list	*current;
	char	**split;
	char	*t;

	if (*input)
		add_history(*input);
	if (check_no_pipe(*input) && check_pipe_input(*input) == -1)
	{
		dprintf(2, "Syntax error: Invalid pipe usage\n");
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
	if (save_data(NULL, cmd, flag, temp) == -1 || *flag == -3)
	{
		if (*flag == -3)
			return (-3);
		return (-1);
	}
	if (searching_comand(input, *temp) == -1)
		return (-1);
	expand_cmds(cmd, robo_env);
	split = ft_split((*temp)[0], ' ');
	if (!split || !*split)
	{
		if (split)
			free(split);
		free(*input);
		return (-3);
	}
	if (ft_strncmp(split[0], "cd", 2) == 0)
	{
		robo_cd(split, robo_env);
		free(*input);
		frees_split(split);
		return (-3);
	}
	frees_split(split);
	if (searching_comand(input, *temp) == -13)
		return (-13);
	t = expander_input((*cmd)->word, robo_env);
	if (execution(cmd, robo_env) == -1)
	{
		free(t);
		free(*input);
		if ((*cmd)->here_doc->file_loc)
			free((*cmd)->here_doc->file_loc);
		if ((*cmd)->here_doc->pryority)
			free((*cmd)->here_doc->pryority);
		if ((*cmd)->exit_status == -13)
			return (-14);
		return (-12);
	}
	free(t);
	free(*input);
	if ((*cmd)->here_doc->file_loc)
		free((*cmd)->here_doc->file_loc);
	free((*cmd)->here_doc->pryority);
	return (0);
}

int	reading_manager(t_cmd **cmd, int *flag, char ***temp, char **robo_env)
{
	char	*input;
	int		ret;

	while ((input = readline(COLOR_CUSTOM "~/Roboshell> " COLOR_RESET)) != NULL)
	{
		if (is_closed(input) == -1)
		{
			dprintf(2, "Syntax error: Unclosed quotes\n");
			free(input);
			continue ;
		}
		ret = process_input(cmd, flag, temp, &input, robo_env);
		if (ret < 0 && ret != -3 && ret != -42 && ret != -55)
		{
			frees_split(*temp);
			free_list((&(*cmd)->word));
			if (ret == -1)
				dprintf(2, "No command found\n");
			if (ret == -12)
			{
				frees_split((*cmd)->env);
				free((*cmd)->here_doc);
				free(*cmd);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		else if (ret == -3 || ret == -14)
		{
			*flag = 0;
			frees_split(*temp);
			free_list(&(*cmd)->word);
			continue ;
		}
		else if (ret == -42)
			continue ;
		frees_split(*temp);
		free_list(&(*cmd)->word);
	}
	printf("Exiting...\n");
	return (0);
}
