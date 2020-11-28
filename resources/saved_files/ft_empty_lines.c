/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_empty_lines.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 18:57:21 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/07 19:04:58 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_printf("----ERROR START---\n");
// ft_printf("----ERROR END---\n");

#include "../minishell.h"
#include <stdio.h>

void        ft_empty_lines(t_struct_m *echo)
{
    t_struct_e empty;

	set_value_empty(&empty);
    empty.s_str = ft_strdup(echo->str);
    free(echo->str);
    while(empty.s_str[empty.begin] && empty.s_str[empty.begin] != '\n')
    {
        empty.begin++;
    }
    echo->str = ft_strdup(empty.s_str);
    free(empty.s_str);
}
