/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 18:29:25 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/26 15:05:33 by nhariman      ########   odam.nl         */
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

static void		ft_parse_exit_argv(char **arr, int len)
{
	int i;
	int check;

	i = 0;
	check = ft_read_array_input(arr[0]);
	if (check >= 0)
	{
		if (len == 1)
			exit(check);
		else
			ft_printf_err("minishell: exit: too many arguments\n");
	}
	else
	{
		ft_printf_err(
			"minishell: exit: %s: numeric argument required\n", arr[0]);
			exit(255);
	}
	return ;
}

static void		exit_main(char *str, t_shell *shell)
{
	int		len;
	char	**argv;

	len = ft_count_arr(str);
	if (len == 0)
		exit(0);
	argv = ft_argv(str, shell);
	if (!argv)
	{
		ft_free_array(argv, len);
		return ;
	}
	ft_parse_exit_argv(argv, len);
	ft_free_array(argv, len);
	shell->exit_code = 1;
	return ;
}

void		exit_minishell(char *str, int *i, t_shell *shell)
{
	int		start;
	t_qts	qts;
	char	*exit_str;

	start = *i;
	ft_set_qts(&qts);
	ft_qt_line(str, &qts, i);
	ft_printf("exit\n");
	exit_str = ft_substr(str, start, *i - start);
	exit_main(exit_str, shell);
	while (str[*i] != '\0')
		*i = *i + 1;
	free(exit_str);
	return ;
}
