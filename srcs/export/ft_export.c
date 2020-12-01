/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 23:27:53 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/01 23:01:06 by nhariman      ########   odam.nl         */
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

	i = 1;
	while (argv[i] != (char *)0)
	{
		valid = ft_valid_envvar(argv[i]);
		if (valid == 1 || valid == 0)
			ft_update_env(shell, argv[i]);
		else if (valid == -1)
		{
			ft_printf_err("omiishell: export: `%s': not a valid identifier\n", argv[i]);
			shell->exit_code = 1;
		}
		i++;
	}
}

void			ft_export(t_shell *shell)
{
	shell->exit_code = 0;
	if (ft_arrlen(shell->argv) == 1)
	{
		shell->ret = ft_make_export_str(shell->env);
		ft_printf("%s\n", shell->ret);
	}
	else
		ft_add_to_env(shell->argv, shell);
}