/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format_export.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 01:46:55 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/27 07:06:08 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_find_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static char		*ft_format_export(char *str)
{
	char	*newstr;
	int		equal;
	char	*name;
	char	*value;
	char	*tmp;

	equal = ft_find_equal(str);
	if (equal > 0)
		name = ft_substr(str, 0, equal + 1);
	else
		name = str;
	newstr = ft_strjointwo("declare -x ", name);
	if (equal > 0)
	{
		value = ft_add_quotations(str, equal + 1);
		tmp = ft_strjoin(newstr, value);
		free(value);
		return (tmp);
	}
	return (newstr);
}

static char		*join_export_str(char **arr)
{
	char	*res;
	char	*tmp;
	int		i;

	res = ft_charjoin(arr[0], '\n');
	i = 1;
	while (arr[i + 1] != (char *)0)
	{
		if (ft_strncmp("declare -x _=", arr[i],
				ft_strlen("declare -x _=")) != 0)
		{
			tmp = gnl_strjoin(res, ft_charjoin(arr[i], '\n'));
			res = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	tmp = gnl_strjoin(res, arr[i]);
	return (tmp);
}

char			*ft_parse_env_str(int *order, char **env)
{
	int		len;
	int		i;
	char	*ret;
	char	**new_env;

	len = ft_arrlen(env);
	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	new_env[len] = (char *)0;
	while (env[i] && order[i] < 127)
	{
		new_env[i] = ft_format_export(env[order[i]]);
		i++;
	}
	ret = join_export_str(new_env);
	return (ret);
}
