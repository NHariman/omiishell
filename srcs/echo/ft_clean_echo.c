/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_clean_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 18:36:24 by ybakker       #+#    #+#                 */
/*   Updated: 2020/12/01 15:30:12 by anonymous     ########   odam.nl         */
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
