/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 21:41:05 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/18 23:34:14 by nhariman      ########   odam.nl         */
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

	len = ft_arrlen(arr) + 1;
	if (len == 0)
		return (NULL);
	i = 0;
	new_argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_argv)
		ft_malloc_fail();
	new_argv[i] = ft_strdup(input);
	free(input);
	while (arr[i] != (char *)0)
	{
		new_argv[i + 1] = ft_strdup(arr[i]);
		i++;
	}
	ft_free_array(arr, ft_arrlen(arr));
	new_argv[i + 1] = (char *)0;
	return (new_argv);
}

char			**ft_add_arr_back(char **arr, char *input)
{
	char	**new_argv;
	int		len;
	int		i;

	len = ft_arrlen(arr) + 1;
	i = 0;
	new_argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_argv)
		ft_malloc_fail();
	while (arr[i] != (char *)0)
	{
		new_argv[i] = ft_strdup(arr[i]);
		i++;
	}
	new_argv[i] = ft_strdup(input);
	new_argv[len] = (char *)0;
	return (new_argv);
}

char			**empty_array(char *cmd)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = cmd;
	arr[1] = (char *)0;
	return (arr);
}
