/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:03 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/01 12:10:48 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_setquotes1(char *first, char value)
{
	*first = value;
}

int	ft_echo_quotes1(char *word, char *ignore)
{
	char	first = '\0';
	int		i = -1;

	while (word[++i])
	{
		if (*ignore == '\0')
			*ignore = first;
		if (word[i] == '\'' && first == '\0')
			ft_echo_setquotes1(&first, '\'');
		else if (word[i] == '\"' && first == '\0')
			ft_echo_setquotes1(&first, '\"');
		else if (word[i] == '\'' && first == '\'')
			ft_echo_setquotes1(&first, '\0');
		else if (word[i] == '\"' && first == '\"')
			ft_echo_setquotes1(&first, '\0');
	}
	if (first != '\0')
		return (-1);
	return (0);
}

char	*skip_quotes(char *split, char ignore)
{
	char	*buff;
	int		i = 0;
	int		j = 0;

	buff = malloc(ft_strlen(split) + 1);
	if (!buff)
		return (NULL);
	while (split[i])
	{
		if (split[i] != ignore)
		{
			buff[j] = split[i];
			j++;
		}
		i++;
	}
	buff[j] = '\0';
	return (buff);
}

static int	handle_quoted(char **buff, char *token, char ignore)
{
	char	*quoted_str;
	char	*tmp;

	quoted_str = skip_quotes(token, ignore);
	if (!quoted_str)
		return (-1);
	if (**buff != '\0')
	{
		tmp = ft_strjoin(*buff, " ");
		free(*buff);
		if (!tmp)
		{
			free(quoted_str);
			return (-1);
		}
		*buff = tmp;
	}
	tmp = ft_strjoin(*buff, quoted_str);
	free(quoted_str);
	free(*buff);
	if (!tmp)
		return (-1);
	*buff = tmp;
	return (0);
}

static int	handle_unquoted(char **buff, char *token)
{
	char	*tmp;

	if (**buff != '\0')
	{
		tmp = ft_strjoin(*buff, " ");
		free(*buff);
		if (!tmp)
			return (-1);
		*buff = tmp;
	}
	tmp = ft_strjoin(*buff, token);
	free(*buff);
	if (!tmp)
		return (-1);
	*buff = tmp;
	return (0);
}

static int	process_token(char **buff, char *token, char *ignore)
{
	int	ret;

	*ignore = '\0';
	ret = ft_echo_quotes1(token, ignore);
	if (ret < 0)
		return (-1);
	if (*ignore)
	{
		ret = handle_quoted(buff, token, *ignore);
		if (ret < 0)
			return (-1);
	}
	else
	{
		ret = handle_unquoted(buff, token);
		if (ret < 0)
			return (-1);
	}
	return (0);
}

int	ft_echo_quotes_manger1(char **split, int *index, char *ignore,
		char **buff)
{
	int	ret;

	*buff = ft_strdup("");
	if (!(*buff))
		return (-1);
	while (split[*index])
	{
		ret = process_token(buff, split[*index], ignore);
		if (ret < 0)
		{
			free(*buff);
			if (ret == -1)
				frees_split(split);
			return (-1);
		}
		(*index)++;
	}
	return (0);
}


int	ft_echo(t_cmd *cmd, t_list *command)
{
    char	**split;
    char	*buff;
    char	ignore = '\0';
    int		i = 1;
    int		n_flag = 0;

    split = ft_split_custom_exp(command->content, ' ');
    if (!split)
        return (-1);
    while (split[i] && ft_strcmp(split[i], "-n") == 0)
    {
        n_flag = 1;
        i++;
    }
	if(ft_echo_quotes_manger1(split, &i, &ignore, &buff) < 0)
		return (-1);
	printf("%s", buff);
	free(buff);
    if (!n_flag)
        printf("\n");
    frees_split(split);
    return (0);
}
