/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_valid_pipe.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 22:39:30 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/01 18:33:38 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_check_back(char *str, int i)
{
	int		j;

	j = 1;
	while (str[i + j] != '\0')
	{
		if (!ft_strchr(" <>;|",str[i + j]))
			return (1);
		j++;
	}
	return (0);
}

static int		ft_check_front(char *str, int i)
{
	int		j;

	j = 1;
	while (i - j != 0)
	{
		if (!ft_strchr(" <>|;",str[i - j]) ||
		!(ft_strchr("<>|;",str[i - j]) && ft_backslash_check(str, i - j) % 2 == 0))
			return (1);
		j++;
	}
	if (!ft_strchr(" <>|;",str[0]))
			return (1);
	else
		return (0);	
}

static int		ft_valid_pipe_input(char *str)
{
	//split on valid |s
	// if any arr is empty, return error?
	int	i;
	int	front;
	int	back;

	i = 0;
	i = i + ft_iswhitespaces(str + i);
	if (str[i] == '|')
		front = 0;
	else
		front = ft_check_front(str, i);
	back = ft_check_back(str, i);
	if (!front)
	{
		ft_printf_err("omiishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!back)
	{
		ft_printf_err("omiishell: syntax error near open pipe `|'\n");
		return (1);
	}
	else
		return (0);
}

static int		ft_contains_pipe(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			return (1);
		if (str[i] == '\\' && str[i + 1] == '|')
			i++;
		i++;
	}
	return (0);
}

int				ft_invalid_pipe(char **arr)
{
	int		j;
	int		res;

	j = 0;
	while(arr[j])
	{	
		if (!ft_contains_pipe(arr[j]))
			j++;
		else
		{
			res = ft_valid_pipe_input(arr[j]);
			if (res == 1)
				return (1);
			j++;
		}
	}
	return (0);
}
