/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:56:32 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/23 21:09:20 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	robo_pwd(void)

{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("%2 error pwd");
		return ;
	}
	ft_printf("%s", pwd);
	free(pwd);
	return ;
}

/*void robo_pwd(char **env)
{
	int i;

	while (env[i])
	{
		if (ft_strcmp(env[i], "PWD") == 0)
		{
			char *eq = ft_strchr(env[i], "=");
			return(eq);
		}
		i++;
	}
	return (0);

}*/