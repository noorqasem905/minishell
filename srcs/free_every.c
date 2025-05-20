/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_every.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:07:21 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/20 19:40:47 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_every(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (cmd->word)
        free_list(&cmd->word);
    if (cmd->here_doc) {
        free(cmd->here_doc->file_loc);
        free(cmd->here_doc->pryority);
        free(cmd->here_doc);
    }
    if (cmd->env)
        frees_split(cmd->env);
    if (cmd->expo)
        frees_split(cmd->expo);
    free(cmd);
}