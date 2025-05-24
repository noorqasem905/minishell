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

static void	error_main(int argc, t_cmd *cmd, char *str)
{
	if (argc > 1)
		exit(EXIT_FAILURE);
	ft_printf("%2 Usage: %s\n", str);
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
	error_main(argc, cmd, argv[0]);
	cmd = malloc(sizeof(t_cmd));
	malloc_error(cmd);
	cmd->here_doc = malloc(sizeof(t_here_doc));
	if (!cmd->here_doc)
		free_main(cmd);
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
// handle end in heredoc that don't incude << end<<