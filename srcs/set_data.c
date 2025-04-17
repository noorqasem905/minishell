/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/17 20:01:01 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

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
void print_saved_cmd(t_list *saved_cmd) {
    t_list *current = saved_cmd;
    while (current != NULL) {
        ft_printf("Command: %s\n", (char *)current->content);
        current = current->next;
    }
}

int     process_input(t_cmd **cmd, int *flag, char ***temp, char **input,  char **robo_env)
{
    if (*input)
        add_history(*input);
    *temp = ft_split(*input, '|');
    // if (searching_comand(input, *temp) == -1)
    //     return (-1);
	if (save_data(NULL, cmd, flag, temp) == -1 || *flag == -3)
    {
        if (*flag == -3)
            return (-3);
		return (-1);
    }
    // expander_input((*cmd)->word, robo_env);
    if (execution(cmd, robo_env) == -1)
    {
        return (-12);
    }
    // execution(cmd, robo_env);
    //     {}// exit(EXIT_FAILURE);
    if (ft_strcmp(*temp[0], "exit") == 0)
	{
        free(*input);
		// free(*input);
        return (-1);
    }
    free(*input);

    return (0);
}

int reading_manager(t_cmd **cmd, int *flag, char ***temp, char **robo_env)
{
    char *input;
    int ret;
     
    while ((input = readline("Roboshell> ")) != NULL)
    {
        ret = process_input(cmd, flag, temp, &input, robo_env);
        if (ret == -1 || ret == -12)
        {
            frees_split(*temp);
            free_list((&(*cmd)->word));        
            dprintf(2,"No command found\n");
            if (ret == -12)
            {
                // There is an issue child process does not die
                free(cmd);
                exit(EXIT_FAILURE);
            }
            break;
        }
        else if (ret == -3)
        {
            *flag = 0;
            frees_split(*temp);
            free_list(&(*cmd)->word);
            continue;
        }
        frees_split(*temp);
        free_list(&(*cmd)->word);
    }
    printf("Exiting...\n");
    return (0);
}
