/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:36:24 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/01 20:30:36 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char	**my_env(char **env)
{
	int		i;
	char	**my_env;

	i = 0;
	while (env[i])
		i++;
	my_env = malloc(sizeof(char *) * (i + 1));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		if (!my_env[i])
		{
			while (--i >= 0)
				free(my_env[i]);
			free(my_env);
			return (NULL);
		}
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

static int	word_count_custuom(char const *s, char c)
{
	int	i;
    int flag = 0;

	i = 0;
	while (*s)
	{
		while (*s == c && *s && *s != '\"')
		{	
            if (*s == '\"')
            {
                flag = 1;
                s++;
            }
            s++;
        }
            if (*s)
			i++;
		while (*s && (*s != c || flag == 1))
        {
            if (*s == '\"')
            {
                flag = 0;
            }
			s++;
        }
    }
	return (i);
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' 
		|| c == '\f' || c == '\r');
}

static void	free_it(char **str, size_t i)
{
	while (i != 0)
	{
		free(str[i]);
		i--;
	}
	free(str[i]);
	free(str);
}

static size_t	word_len_custuom(char *s, char c, int *flag)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c || *flag))
	{
		if (s[i] == '\"')
		{
			*flag = !(*flag);
			i++;
			continue;
		}
		i++;
	}
	return (i);
}

char	**ft_split_custom_exp(char const *s, char c)
{
	char	**str;
	size_t	i;
    int flag = 0;

	i = 0;
	str = malloc(sizeof(char *) * (word_count_custuom(s, c) + 1));
	if (!s || !str)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			str[i] = ft_substr(s, 0, word_len_custuom((char *)s, c, &flag));
			if (!str[i++])
			{
				free_it(str, i - 1);
				return (NULL);
			}
			s += word_len_custuom((char *)s, c, &flag);
		}
	}
	str[i] = NULL;
	return (str);
}

static int	word_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}


static size_t	word_len(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}
void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n",str, split[i]);
		i++;
	}
}


static void print_export(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->env[i])
	{
		ft_printf("declare -x %s\n", cmd->env[i]);
		i++;
	}
}
static void add_fuc(t_cmd *cmd, char *name, char *value)
{
	int i;
	int name_len;
	char *new_var;
	int j;

	i = 0;
	name_len = ft_strlen(name);
	new_var= ft_strjoin(ft_strjoin(name, "="), value);
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], name, name_len) && cmd->env[i][name_len] == '=')
		{
			free(cmd->env[i]);
			cmd->env[i] = new_var;
			return;
		}
		i++;
	}
	char **new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return;
	j = 0;
	while (j < i)
	{
		new_env[j] = cmd->env[j];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(cmd->env);
	cmd->env = new_env;
}

static void robo_export(t_cmd *cmd, t_exp *export)
{
	int i;
	
	i = 0;
	if (!export->name[0])
	{
		print_export(cmd);
		return ;
	}
	while (export->name[i])
	{
		fuc_add(cmd, export->name[i], export->value[i]);
		i++;
	}
	
}

int	main(int argc, char **argv, char **env)
{
	char *str = "	export x1 =\"123\" ttt=dfdfd x2 x3=\"wdd\" ";
    char *e = "export";
	char delimiter = ' ';
	char **result;
	t_exp *export;
	int i;
	int len; 
	t_cmd *cmd;
	
	cmd->env = my_env(env);
	len = 0;
	if (!ft_strmchr(str, "export"))
		return (1);
	result = ft_split_custom_exp(str, delimiter);
 	if (result == NULL)
	{
		ft_printf("%2Error: ft_split failed\n");
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
	if (ft_strcmp(result[0], "export"))
	{
		printf("Error");
		frees_split(result);
		return (-60);
	}
	i = 0;
	while (result[i])
		i++;
	export =  malloc(sizeof(t_exp));
 	export->name = ft_calloc(i, sizeof(char *));
	export->value = ft_calloc(i, sizeof(char *));
	if (!export->name || !export->value)
    {
        ft_printf("%2Error: Memory allocation failed for export->name or export->value\n");
        free(export->name);
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
			export->value[j] = ft_strdup(result[x + 1] + 1);
			x++;
		}
		else if (ft_strchr(result[x], '='))
		{
			len = word_len(result[x], '=');
			export->name[j] = ft_substr(result[x], 0, len);
			export->value[j] = ft_strdup(result[x] + len + 1);
		}
		else
		{
			export->name[j] = ft_strdup(result[x]);
			export->value[j] = ft_strdup("");
		}
		x++;
		j++;
	}
	export->name[x - 1] = NULL;
	export->value[x - 1] = NULL;
	
	robo_export(cmd, export);
	printf_split("NAME: ", export->name);
	printf_split("VALUE: ", export->value);
	frees_split(export->name);
	frees_split(export->value);
	frees_split(result);
	free(export);
	return (0);
}
