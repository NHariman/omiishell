/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_directory.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 21:54:48 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/22 00:07:35 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_is_directory(char *cmd, t_shell *shell)
{
	struct stat	statbuf;
	int			check;

	check = lstat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		shell->exit_code = 126;
		return (ft_printf_err("omiishell: %s: is a directory\n", shell->argv[0]));
	}
	return (0);
}