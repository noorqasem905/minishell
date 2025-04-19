/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#          
/*   Updated: 2025/04/19 18:42:48 by nqasem           ###   ########.fr       */
/*   Updated: 2025/04/19 15:31:27 by aalquraa         ###   ########.fr       */
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
	if (save_data(NULL, cmd, flag, temp) == -1 || *flag == -3)
    {
        if (*flag == -3)
            return (-3);
		return (-1);
    }
    char **split;
    split = ft_split((*temp)[0], ' ');
    if (ft_strncmp(split[0], "cd", 2) == 0)
    {
        robo_cd(split, robo_env);
        free(*input);
        return (-3);
    }
    if (searching_comand(input, *temp) == -13)
        return (-13);
    // expander_input((*cmd)->word, robo_env);
    if (execution(cmd, robo_env) == -1)
    {
        return (-12);
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
        if (ret < 0 && ret != -3)
        {
            frees_split(*temp);
            free_list((&(*cmd)->word));
            if (ret == -1)
                dprintf(2,"No command found\n");
            if (ret == -12)
            {
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
