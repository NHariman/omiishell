/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 23:27:53 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/27 08:28:41 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		*ft_make_export_str(char **env)
{
	int		*order;
	char	*export_str;

	order = ft_order_env(env);
	ft_sort_env(order, env, 1);
	export_str = ft_parse_env_str(order, env);
	return (export_str);
}

int				ft_valid_envvar(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '/')
			return (-1);
		else if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void		ft_add_to_env(char **argv, t_shell *shell)
{
	int		i;
	int		valid;

	i = 0;
	while (argv[i] != (char *)0)
	{
		valid = ft_valid_envvar(argv[i]);
		if (valid == 1 || valid == 0)
			ft_update_env(shell, argv[i]);
		else if (valid == -1)
			ft_printf_err("minishell: export: `%s': not a valid identifier\n", argv[i]);
		i++;
	}
}

int			ft_export(char *str, t_shell *shell)
{
	char	**argv;
	int		len;

	shell->exit_code = 0;
	len = ft_count_arr(str);
	if (len == 0)
		shell->exprt = ft_make_export_str(shell->env);
	else
	{
		argv = ft_argv(str, shell);
		if (!argv)
			shell->exprt = ft_make_export_str(shell->env);
		else
			ft_add_to_env(argv, shell);
	}
	if (len == 0 || !argv)
	{
		shell->check.exp = 1;
		return (0);
	}
	return (1);
}