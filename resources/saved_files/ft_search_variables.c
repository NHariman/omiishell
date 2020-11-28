/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_search_variables.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 20:56:01 by anonymous     #+#    #+#                 */
/*   Updated: 2020/11/07 16:31:10 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_printf("----ERROR START---\n");
// ft_printf("----ERROR END---\n");

#include "../minishell.h"
#include <stdio.h>

//check if the variable is correct and what input needs to be taken out
//else if its false, return nothing

int    ft_search_variable(t_struct_em *trim, char *str)
{
	//check if the variable is there, if not, then return an empty string
	int i;

	i = 0;
	if (ft_strncmp("$PATH", str, 4) == 0)
	{
		trim->s_end = ft_pwd();
		i = ft_strlen(trim->s_end);
		trim->begin = trim->begin + i;
		return (0);
	}
	trim->s_end = ft_strdup("");
	return (1);
}
