/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 21:15:13 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/01 23:03:13 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_malloc_fail(void)
{
	ft_printf_err("Error\nMalloc failed. Exiting program.\n");
	exit(1);
}

void	ft_free_array(char **arr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

static void	ft_free_shell(char *str)
{
	str = NULL;
	free(str);
}

void	ft_clear_shell(t_shell *shell)
{
	shell->fd = -1;
	shell->oldnb = 0;
	if (shell->ret != (char *)0)
		ft_free_shell(shell->ret);
	if (shell->argv != (char **)0)
		ft_free_array(shell->argv, ft_arrlen(shell->argv));
	if (shell->rd_r != (char *)0)
		ft_free_shell(shell->rd_r);
	if (shell->rds != (char *)0)
		ft_free_shell(shell->rds);
}
