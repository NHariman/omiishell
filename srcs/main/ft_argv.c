/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_argv.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 19:01:09 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/30 00:44:27 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_skip_quotes(char *str, int *i, int type)
{
	*i = *i + 1;
	if (type == SQ)
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
	}
	else if (type == DQ)
	{
		while (str[*i] != '\"' && str[*i] != '\0')
		{
			if (str[*i] == '\\' && ft_strchr("\\\"", str[*i + 1]))
				*i = *i + 2;
			else
				*i = *i + 1;
		}
	}
	*i = *i + 1;
}

static void	ft_skip_through(char *str, int *i)
{
	while ((str[*i] != ' ' && str[*i] != '\0'))
	{
		if (str[*i] == '\"' && ft_backslash_check(str, *i) % 2 == 0)
			ft_skip_quotes(str, i, DQ);
		else if (str[*i] == '\'' && ft_backslash_check(str, *i) % 2 == 0)
			ft_skip_quotes(str, i, SQ);
		else if (str[*i] == '\\' && ft_strchr(" \\\'\"", str[*i + 1]))
			*i = *i + 2;
		else
			*i = *i + 1;
	}
}

int		ft_count_arr(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("<>|", str[i]) && ft_backslash_check(str, i) % 2 == 0)
			ft_skip_rd(str, &i);
		else if (str[i] != ' ')
		{
			ft_skip_through(str, &i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_make_array(char **arr, char *str, t_shell *shell, int arr_len)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0' && count < arr_len)
	{
		if (str[i] != ' ')
		{
			arr[count] = ft_no_quotes_str(str, &i, shell);
			if (!arr[count])
				return (NULL);
			count++;
		}
		else
			i++;
	}
	arr[arr_len] = (char *)0;
	return (arr);
}

char		**ft_argv(char *s, t_shell *shell)
{
	char	**split;
	int		arr_len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	arr_len = ft_count_arr(s);
	if (arr_len == 0)
		return (NULL);
	split = (char **)malloc((arr_len + 1) * sizeof(char *));
	if (!split)
		ft_malloc_fail();
	split = ft_make_array(split, s, shell, arr_len);
	if (!split)
		ft_malloc_fail();
	return (split);
}
