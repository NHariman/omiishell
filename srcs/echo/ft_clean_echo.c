/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_clean_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 18:36:24 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/15 17:29:33 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void		set_value_echo(t_struct_m *echo)
{
	echo->n = 0;
	echo->i = 0;
}

void		set_value_trim(t_struct_tr *trim)
{
	trim->begin = 0;
	trim->end = 0;
	trim->single = 0;
	trim->doubble = 0;
	trim->quote = 0;
	trim->empty = 0;
	trim->error = 0;
}

void		set_value_rd(t_struct_rd *rd)
{
	rd->error = 0;
	rd->single = 0;
	rd->doubble = 0;
	rd->echo = 0;
	rd->variable = 0;
	rd->dir = 0;
}
