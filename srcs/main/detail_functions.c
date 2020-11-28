/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   detail_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 18:50:43 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/26 20:44:44 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** for improvement: copy the cmd word, lowercase it, compare it
** to echo and pwd, if correct, return the lowercased word
** else return the original.
*/

char		*ft_find_case_cmd(char *cmd)
{
	char *tmp;

	tmp = NULL;
	if (!ft_strcasecmp(cmd, "echo") || !ft_strcasecmp(cmd, "env") ||
		!ft_strcasecmp(cmd, "pwd"))
		tmp = ft_strlower(cmd);
	else
		tmp = ft_strdup(cmd);
	free(cmd);
	return (tmp);
}
