/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_update_env.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 04:53:31 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/20 17:52:55 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_find_varname(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		name = ft_strdup(str);
	else
		name = ft_substr(str, 0, i);
	return (name);
}

static void		ft_update_shell(t_shell *shell, char *str, char *var)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (shell->env[i])
	{
		name = ft_find_varname(shell->env[i]);
		if (ft_strcmp(name, var) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(str);
			free(name);
			return ;
		}
		if (name)
			free(name);
		i++;
	}
	
}

void			ft_update_env(t_shell *shell, char *str)
{
	char	*var;
	char	**newenv;
	char	*findenv;

	var = ft_find_varname(str);
	findenv = ft_find_envvar(var, shell);
	if (findenv == NULL)
	{
		newenv = ft_add_arr_back(shell->env, str);
		ft_free_array(shell->env, ft_arrlen(shell->env));
		shell->env = newenv;
	}
	else
		ft_update_shell(shell, str, var);
	if (findenv)
		free(findenv);
	free(var);
}