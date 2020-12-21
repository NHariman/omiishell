/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 21:15:13 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/08 20:52:13 by nhariman      ########   odam.nl         */
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
	shell->check.echo = 0;
	shell->check.env = 0;
	shell->check.exp = 0;
	shell->check.exec = 0;
	shell->check.err = 0;
	shell->check.pwd = 0;
	shell->fd = -1;
	shell->oldnb = 0;
	if (shell->argv != NULL)
		ft_free_array(shell->argv, ft_arrlen(shell->argv));
	if (shell->ret != (char *)0)
		ft_free_shell(shell->ret);
	if (shell->echo != (char *)0)
		ft_free_shell(shell->echo);
	if (shell->pwd != (char *)0)
		ft_free_shell(shell->pwd);
	if (shell->env_s != (char *)0)
		ft_free_shell(shell->env_s);
	if (shell->exprt != NULL)
		ft_free_shell(shell->exprt);
	if (shell->err != (char *)0)
		ft_free_shell(shell->err);
}
