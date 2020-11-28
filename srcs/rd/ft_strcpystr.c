/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpystr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 19:10:53 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/21 19:40:11 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char    *ft_strcpystr(int start, char *str, char c)
{
	int		i;
	char	*string;

	i = start;
	while (str[i] != c)
		i++;
	string = (char *)malloc((i - start + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[start] != c)
	{
		string[i] = str[start];
		i++;
		start++;
	}
	string[i] = '\0';
	return (string);
}
