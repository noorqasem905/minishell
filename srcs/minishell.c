/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 17:53:47 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	error_main(int argc, char **str)
{
	if (str[0])
		;
	if (argc > 1)
		exit(EXIT_FAILURE);
}

static void	malloc_error(void *err)
{
	if (err == NULL)
	{
		ft_printf("%2 Malloc Error");
		exit(EXIT_FAILURE);
	}
}

static void	free_main(void *mal)
{
	if (!mal)
		return ;
	free(mal);
	exit(0);
}

static void	ft_env(t_cmd **cmd, char **robo_env)
{
	(*cmd)->env = my_env(robo_env);
	if (!(*cmd)->env)
	{
		free((*cmd)->here_doc);
		free(*cmd);
		exit(0);
	}
	save_export_to_expo(cmd);
	if (!(*cmd)->expo)
	{
		frees_split((*cmd)->env);
		free((*cmd)->here_doc);
		free(*cmd);
		exit(0);
	}
}

int	main(int argc, char *argv[], char **robo_env)
{
	t_cmd	*cmd;
	char	*input;
	char	**temp;
	int		flag;
	int		e;

	e = 0;
	input = NULL;
	temp = NULL;
	error_main(argc, argv);
	cmd = malloc(sizeof(t_cmd));
	malloc_error(cmd);
	cmd->here_doc = malloc(sizeof(t_here_doc));
	if (!cmd->here_doc)
		free_main(cmd);
	init_data(&cmd);
	ft_env(&cmd, robo_env);
	reading_manager(&cmd, &flag, &temp);
	frees_split(cmd->env);
	frees_split(cmd->expo);
	free(cmd->here_doc);
	e = cmd->exit_status;
	free(cmd);
	return (e);
}
// cat ^\ exit cat
