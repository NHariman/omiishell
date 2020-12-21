/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skip_quotes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 20:32:54 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/06 20:51:28 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_skip_quotes(char *str, int *i, char type)
{
	*i = *i + 1;
	if (type == '\'')
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
	}
	else if (type == '\"')
	{
		while (str[*i] != '\"' && str[*i] != '\0')
		{
			if (str[*i] == '\\' && ft_strchr("\\\"", str[*i + 1]))
				*i = *i + 2;
			else
				*i = *i + 1;
		}
	}
	*i = *i + 1;
}
