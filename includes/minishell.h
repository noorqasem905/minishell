/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:43:02 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/05 21:21:29 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
typedef struct s_cmd        t_cmd;
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include "../libft/printf/ft_printf.h"
# include "../libft/libft.h"
struct          s_cmd
{
    t_list            *word;
};
int read_input(char **input);
int save_data(char **input, t_cmd **cmd, int *flag);
void	frees(t_list **root);


#endif