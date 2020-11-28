/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 17:45:23 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/26 15:37:25 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** first argument is executable
** every other argument thereafter is part of an argv that should be passed
** into the executable.
** use execv, this will return 0 if succesful, and -1 if error.
** shell->exit_err set to 126 for unable to execute. (unless you use a fork?)
*/

/*
** make a linked list of args if the first arg does not contain an = for
** VARIABLE=CONENT
** and execute the command while giving the envp and argv list, if
** that is the only command out there. If not, store it and wait for
** the redirection or pipe.
*/

static char	*ft_make_env_str(t_shell *shell)
{
	int		len;
	int		i;
	char	*new_str;
	char	*tmp;

	len = ft_envlen(shell);
	new_str = ft_charjoin(shell->env[0], '\n');
	i = 1;
	while (i < len - 1)
	{
		tmp = gnl_strjoin(new_str, ft_charjoin(shell->env[i], '\n'));
		new_str = tmp;
		i++;
	}
	tmp = gnl_strjoin(new_str, shell->env[i]);
	new_str = tmp;
	return (new_str);
}

int			env_main(char *str, t_shell *shell)
{
	size_t	j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] != ' ' && str[j] != '\n')
			break ;
		j++;
	}
	if (j == ft_strlen(str))
	{
		shell->env_s = ft_make_env_str(shell);
		shell->exit_code = 0;
		return (1);
	}
	else
	{
		ft_printf_err("minishell: env: too many arguments.\n");
		shell->exit_code = 1;
	}
	return (0);
}
