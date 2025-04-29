/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/29 20:04:32 by aalquraa         ###   ########.fr       */
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

int	process_input(t_cmd **cmd, int *flag, char ***temp, char **input,
		char **robo_env)
{
	t_list	*current;
	char	**split;

	if (*input)
		add_history(*input);
	*temp = ft_split(*input, '|');
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
	if (ft_strncmp(split[0], "cd", 2) == 0)
	{
		robo_cd(split, robo_env);
		free(*input);
		frees_split(split);
		return (-3);
	}
	if (ft_strncmp(split[0], "export", 7) == 0)
	{
		robo_env= exp(split, &robo_env);
		free(*input);
		frees_split(split);
		return (-3);
	}
	frees_split(split);
	if (searching_comand(input, *temp) == -13)
		return (-13);
	char *t = expander_input((*cmd)->word, robo_env);
 	if (execution(cmd, robo_env) == -1)
	{
		free(t);
		free(*input);
		return (-12);
	}
	free(t);
	free(*input);
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
		if (ret < 0 && ret != -3)
		{
			frees_split(*temp);
			free_list((&(*cmd)->word));
			if (ret == -1)
				dprintf(2, "No command found\n");
			if (ret == -12)
			{
				frees_split((*cmd)->env);
				free(*cmd);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		else if (ret == -3)
		{
			*flag = 0;
			frees_split(*temp);
			free_list(&(*cmd)->word);
			continue ;
		}
		frees_split(*temp);
		free_list(&(*cmd)->word);
	}
	printf("Exiting...\n");
	return (0);
}
