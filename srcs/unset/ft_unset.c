/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 23:27:27 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/01 21:37:04 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		ft_delete_env(t_shell *shell, char *var)
{
	int		i;
	int		j;
	int		len;
	char	*env;
	char	**newenv;

	i = 0;
	j = 0;
	len = ft_arrlen(shell->env);
	newenv = (char **)malloc(sizeof(char *) * len);
	if (!newenv)
		ft_malloc_fail();
	newenv[len - 1] = (char *)0;
	while (shell->env[i])
	{
		env = ft_find_varname(shell->env[i]);
		if (ft_strcmp(env, var) != 0)
		{
			newenv[j] = ft_strdup(shell->env[i]);
			j++;
		}
		i++;
	}
	shell->env = newenv;
}

static void		ft_remove_env(char **argv, t_shell *shell)
{
	int		i;

	i = 1;
	while (argv[i] != (char *)0)
	{
		if (ft_valid_envvar(argv[i]) == -1)
		{
			ft_printf_err(
				"omiishell: export: `%s': not a valid identifier\n", argv[i]);
		}
		else if (ft_find_envvar(argv[i], shell) != NULL)
			ft_delete_env(shell, argv[i]);
		i++;
	}
}

void			ft_unset(t_shell *shell)
{
	if (ft_arrlen(shell->argv) == 1)
		return ;
	ft_remove_env(shell->argv, shell);
	return ;
}