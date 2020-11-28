/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_nflag.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 12:54:04 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/21 16:17:38 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static int	is_flag_ok(char	*str, int i)
{
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != ' ')
		return (1);
	return (0);
}

int			check_flag_n(t_struct_m *echo)
{
	echo->s = 0;
	echo->i = skip_character(echo->str, echo->i, ' ');
	while (echo->str[echo->i] == '-')
	{
		if (is_flag_ok(echo->str, echo->i) == 1)
			return (echo->i);
		echo->s = echo->i;
		echo->i++;
		if (echo->str[echo->i] != 'n')
			return (echo->s);
		if (echo->str[echo->i] == 'n')
			echo->i = skip_character(echo->str, echo->i, 'n');
		if (echo->str[echo->i] == ' ')
		{
			echo->n = 1;
			echo->i = skip_character(echo->str, echo->i, ' ');
		}
		if (echo->str[echo->i] == '\n' || echo->str[echo->i] == '\0')
		{
			echo->n = 1;
			return (echo->i);
		}
	}
	return (echo->i);
}
