/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 21:41:05 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/29 22:15:13 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != (char *)0)
		i++;
	return (i);
}

char			**ft_add_arr_front(char **arr, char *input)
{
	char	**new_argv;
	int		len;
	int		i;

	len = ft_arrlen(arr);
	if (len == 0)
		return (NULL);
	i = 0;
	new_argv = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		ft_malloc_fail();
	new_argv[i] = ft_strdup(input);
	new_argv[len + 1] = (char *)0;
	while (i + 1 < len + 1)
	{
		new_argv[i + 1] = ft_strdup(arr[i]);
		i++;
	}
	ft_free_array(arr, len);
	return (new_argv);
}

char			**ft_add_arr_back(char **arr, char *input)
{
	char	**new_argv;
	int		len;
	int		i;

	len = ft_arrlen(arr);
	i = 0;
	new_argv = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		ft_malloc_fail();
	new_argv[len] = ft_strdup(input);
	new_argv[len + 1] = (char *)0;
	while (i < len)
	{
		new_argv[i] = ft_strdup(arr[i]);
		i++;
	}
	return (new_argv);
}

char			**empty_array(char *cmd)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup(cmd);
	arr[1] = (char *)0;
	return (arr);
}
