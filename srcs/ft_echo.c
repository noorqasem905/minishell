/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:03 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/29 15:10:08 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo_free_join_args(char **joined, char *tmp, char **buff)
{
	*joined = ft_strjoin(*buff, " ");
	free(*buff);
	*buff = ft_strjoin(*joined, tmp);
	free(*joined);
	free(tmp);
}

static char	*echo_join_args(char **split, int i)
{
	char	*buff;
	char	*tmp;
	char	*joined;

	buff = NULL;
	while (split[i])
	{
		tmp = strip_outer_quotes(split[i]);
		if (!tmp)
		{
			if (buff)
				free(buff);
			return (NULL);
		}
		if (!buff)
			buff = tmp;
		else
			echo_free_join_args(&joined, tmp, &buff);
		i++;
	}
	return (buff);
}

int	ft_echo(t_cmd *cmd, t_list *command)
{
	char	new_line;
	char	**args;
	int		i;

	new_line = '\n';
	args = ft_split_custom_exp(command->content, ' ');
	if (!args)
		return (-1);

	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		new_line = '\0';
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("%c", new_line);
	frees_split(args);
	return (0);
}
