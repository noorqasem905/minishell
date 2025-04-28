/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#    #+#      		  */
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

	input = NULL;
	temp = NULL;
	cmd = malloc(sizeof(t_cmd));
	cmd->env = NULL;
	cmd->exit_status = 0;
	if (cmd == NULL)
	{
		perror("malloc");
		return (1);
	}
	cmd->word = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		free(cmd);
		return (1);
	}
	cmd->env = my_env(robo_env);
	reading_manager(&cmd, &flag, &temp, cmd->env);
	frees_split(cmd->env);
	free(cmd);
	return (0);
}
