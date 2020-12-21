/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_invalid_line.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 19:44:11 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/22 00:09:11 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			ft_skip_cmd(int *check, char *str, int *i, int token)
{
	*check = 1;
	while (str[*i] != token && str[*i] != '\0')
	{
		if (ft_strchr("\'\"", str[*i]) && ft_backslash_check(str, *i) % 2 == 0)
			ft_skip_quotes(str, i, str[*i]);
		else if (str[*i] == '\\')
			*i = *i + 2;
		else if (ft_strchr("<>", str[*i]) &&
		str[*i + 1 + ft_iswhitespaces(str + *i + 1)] == token)
		{
			*check = -1;
			*i = *i + 1;
		}
		else
			*i = *i + 1;
	}
	if (str[*i + 1 + ft_iswhitespaces(str + *i + 1)] == token ||
	str[*i + 1 + ft_iswhitespaces(str + *i + 1)] == '\0')
	{
		if ((str[*i + 1 + ft_iswhitespaces(str + *i + 1)] == token &&
		token == ';') || token == '|')
			*check = -1;
	}
	else if (*check != -1)
		*i = *i + 1;
}

int					ft_invalid_line(char *str, t_shell *shell, char token)
{
	int			i;
	int			check;

	i = 0;
	check = -1;
	while (str[i] != '\0')
	{
		i = i + ft_iswhitespaces(str + i);
		if (str[i] == token && check == -1)
		{
			shell->exit_code = 258;
			return (ft_printf_err(
			"omiishell: syntax error near unexpected token `%c'\n", token));
		}
		else if (str[i] != ' ' &&
			str[i + 1 + ft_iswhitespaces(str + i + 1)] != '\0' &&
			str[i] != token)
			ft_skip_cmd(&check, str, &i, token);
		else
			i++;
	}
	return (0);
}
