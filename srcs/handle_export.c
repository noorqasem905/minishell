/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:36:24 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/18 16:27:47 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static size_t	word_lenn(char *s, char c)
{
    size_t	i;
    
	i = 0;
	while (s[i] && s[i] != c)
	{
        i++;
	}
	return (i);
}
static char *trim_quotess(char *str)
{

	return ft_strtrim(str, "\"");
}


void	free_it(char **str, size_t i)
{
	while (i != 0)
	{
		free(str[i]);
		i--;
	}
	free(str[i]);
	free(str);
}

int ft_export(char *str, t_cmd **cmd)
{
	char **result;
	t_exp *export;
	int i;
	int len;
	
	len = 0;
	result = ft_split_custom_exp(str, ' ');
 	if (result == NULL)
	{
		ft_printf("%2Error: ft_split failed\n");
		(*cmd)->exit_status = 2;
		return (1);
	}
	int m = 0;
    while (result[0] && result[0][m] == '\t')
        m++;
    if (m > 0)
    {
        char *tmp = malloc(ft_strlen(result[0]) - m + 1);
        if (!tmp)
        {
            ft_printf("%2Error: Memory allocation failed for tmp\n");
            frees_split(result);
            return (1);
        }
        int kk = 0;
        while (result[0][m])
        {
            tmp[kk] = result[0][m];
            kk++;
            m++;
        }
        tmp[kk] = '\0';
        free(result[0]);
        result[0] = tmp;
    }
	i = 0;
	while (result[i])
		i++;
	export =  malloc(sizeof(t_exp));
 	export->name = ft_calloc(i + 1, sizeof(char *));
	export->value = ft_calloc(i + 1, sizeof(char *));
	if (!export->name || !export->value)
    {
        ft_printf("%2Error: Memory allocation failed for export->name or export->value\n");
        if (export->name)
			free(export->name);
		if (export->value)
			free(export->value);
        free(export);
        frees_split(result);
        return (-60);
    }
	int x = 1;
	int y = 0;
	int j = 0;
 	while (result[x])
	{
		if (result[x + 1] && result[x + 1][0] == '=')
		{
			export->name[j] = ft_strdup(result[x]);
			export->value[j] = trim_quotess(result[x + 1] + 1);
			x++;
		}
		else if (ft_strchr(result[x], '='))
		{
			len = word_lenn(result[x], '=');
			export->name[j] = ft_substr(result[x], 0, len);
			export->value[j] = trim_quotess(result[x] + len + 1);
		}
		else
		{
			export->name[j] = ft_strdup(result[x]);
			export->value[j] = ft_strdup("");
		}
		x++;
		j++;
	}
	export->name[j]= NULL;
	export->value[j] = NULL;
	// printf_split("NAME: ", export->name);
	// printf_split("VALUE: ", export->value);
	// printf("%d\n", j);
	// printf("%s", export->name[0]);
	// printf("*****export*********\n");
	robo_export(cmd, export);
	frees_split(export->name);
    frees_split(export->value);
    free(export);
    frees_split(result);
    return (0);
}
