/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 23:27:27 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/22 00:09:23 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		**ft_delete_arr_entry(char **arr, char *var)
{
	int		i;
	int		j;
	int		len;
	char	*env;
	char	**newenv;

	i = 0;
	j = 0;
	len = ft_arrlen(arr);
	newenv = (char **)malloc(sizeof(char *) * len);
	if (!newenv)
		ft_malloc_fail();
	newenv[len - 1] = (char *)0;
	while (arr[i])
	{
		env = ft_find_varname(arr[i]);
		if (ft_strcmp(env, var) != 0)
		{
			newenv[j] = ft_strdup(arr[i]);
			j++;
		}
		free(env);
		i++;
	}
	return (newenv);
}

static void		ft_delete_env(t_shell *shell, char *input)
{
	char **newenvp;

	newenvp = ft_delete_arr_entry(shell->env, input);
	ft_free_array(shell->env, ft_arrlen(shell->env));
	shell->env = newenvp;
}

static void		ft_remove_env(char **argv, t_shell *shell)
{
	int		i;
	char	*envvar;

	i = 1;
	envvar = NULL;
	while (argv[i] != (char *)0)
	{
		envvar = ft_find_envvar(argv[i], shell);
		if (ft_valid_envvar(argv[i]) == -1)
		{
			ft_printf_err(
				"omiishell: export: `%s': not a valid identifier\n", argv[i]);
		}
		else if (envvar != NULL)
			ft_delete_env(shell, argv[i]);
		if (envvar)
			free(envvar);
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