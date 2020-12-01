/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 18:29:25 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/01 20:06:48 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** find first argument, if first argument is not a number keep looking.
** if number argument is found, check for anything that isn't ' ' or
** ><;|\n or \0.
*/

/*
** exit code: 255 for if a numeric value is found but it contains alpha chars, also use the first arg found as error message. but still exit.
** ie. exit hello 12cab
** program exits with exit code 255, hello is used as arg.
** for exit 123 abc
** the program will NOT exit, it will print a warning: too many arguments.
** for exit hello 123
** the program WILL exit with exit code 123
*/

static int		ft_read_array_input(char *str)
{
	int check;
	int i;
	int len;

	check = -1;
	i = 0;
	if (!str)
		return (0);
	len = ft_strlen(str);
	while (!ft_isdigit(str[i]) && str[i] != '\0' &&
				str[i] != '-' && str[i] != '+')
		i++;
	if (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
	{
		if ((str[i] == '-' && !ft_isdigit(str[i + 1])) || (str[i] == '+'
			&& !ft_isdigit(str[i + 1])))
			return (-1);
		check = ft_atoi(str + i);
		while (ft_isdigit(str[i]) && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			return (-1);
	}
	return (check);
}

void			ft_exit_minishell(char **arr, int len, t_shell *shell)
{
	int check;

	ft_printf("exit\n");
	check = ft_read_array_input(arr[1]);
	if (check >= 0)
	{
		if (len < 3)
			exit(check);
		else
			ft_printf_err("omiishell: exit: too many arguments\n");
	}
	else
	{
		ft_printf_err(
			"omiishell: exit: %s: numeric argument required\n", arr[0]);
			exit(255);
	}
	shell->exit_code = 1;
	return ;
}
