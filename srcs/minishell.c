/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#             */
/*   Updated: 2025/04/06 12:20:41 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[])
{
	t_cmd	*cmd;
	char	*input;
	char	**temp;
	int		flag;

	input = NULL;
	temp = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		perror("malloc");
		return (1);
	}
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		free(cmd);
		return (1);
	}
    cmd->word = NULL;
    reading_manager(&cmd, &flag, &temp);
	free(cmd);
	return (0);
}
