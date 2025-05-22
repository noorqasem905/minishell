/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#    #+#			  */
/*   Updated: 2025/04/06 12:20:41 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	cmd = malloc(sizeof(t_cmd));
	cmd->here_doc = malloc(sizeof(t_here_doc));
	if (cmd == NULL)
	{
		ft_printf("%2malloc");
		return (1);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		free(cmd);
		return (1);
	}
	init_data(&cmd);
	cmd->env = my_env(robo_env);
	save_export_to_expo(&cmd);
	reading_manager(&cmd, &flag, &temp, cmd->env);
	frees_split(cmd->env);
	frees_split(cmd->expo);
	free(cmd->here_doc);
	e = cmd->exit_status;
	free(cmd);
	return (e);
}



