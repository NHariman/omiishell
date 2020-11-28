/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execv.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 23:27:59 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/26 19:53:36 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** returns several exit, returns 1 if execution failed
** returns 127 if the executable was not found in the $PATH variable.
*/

static int		ft_ispath(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int		ft_execute_path(char **pathcmd, char **argv, t_shell *shell)
{
	pid_t	child_pid;
	pid_t	tpid;
	int		i;
	int		child_status;

	i = 0;
	tpid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		while (pathcmd[i] != (char *)0)
		{
			execve(pathcmd[i], argv, shell->env);
			i++;
		}
		ft_printf_err("minishell: %s: command not found.\n", argv[0],
		strerror(errno));
		exit(1);
	}
	else
	{
		while (tpid != child_pid)
			tpid = wait(&child_status);
	}
	return (child_status);
}

static int		ft_execve_path(char *cmd, char **argv, t_shell *shell)
{
	int		child_status;
	char	**pathcmd;

	errno = 0;
	shell->exit_code = 0;
	pathcmd = ft_path_array(ft_find_envvar("PATH", shell), cmd);
	child_status = ft_execute_path(pathcmd, argv, shell);
	if (child_status != 0)
		shell->exit_code = 127;
	return (0);
}

int				ft_execve(char **argv, t_shell *shell)
{
	pid_t	child_pid;
	pid_t	tpid;
	int		child_status;

	errno = 0;
	tpid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(argv[0], argv, shell->env);
		ft_printf_err("minishell: %s: %s\n", argv[0],
		strerror(errno));
		exit(1);
	}
	else
	{
		while (tpid != child_pid)
			tpid = wait(&child_status);
	}
	if (child_status != 0)
		shell->exit_code = 1;
	return (0);
}

void			ft_execute(char *cmd, char *str, char end, t_shell *shell)
{
	char	**argv;
	int		len;
	char	**tmp;

	shell->exit_code = 0;
	len = ft_count_arr(str);
	if (len == 0)
		argv = empty_array(cmd);
	else
	{
		tmp = ft_argv(str, shell);
		argv = ft_add_arr_front(tmp, cmd);
	}
	if (ft_strchr("\n;\0", end))
	{
		if (ft_ispath(cmd))
			ft_execve(argv, shell);
		else
			ft_execve_path(cmd, argv, shell);
		ft_free_array(argv, len);
	}
	else
		shell->argv = argv;
	return ;
}
