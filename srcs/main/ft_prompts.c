/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prompts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 03:18:41 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/01 18:48:59 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_prompts(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && ft_backslash_check(str, i) % 2 == 0)
			ft_skip_quotes(str, &i, DQ);
		else if (str[i] == '\'' && ft_backslash_check(str, i) % 2 == 0)
			ft_skip_quotes(str, &i, SQ);
		else
			i = i + 1;
		if (str[i] == ';' && ft_backslash_check(str, i) % 2 == 0 &&
		str[i + 1] != '\0')
			count++;
	}
	return (count);
}

static char	**ft_fill_prompts(char **prompts, char *str, int len)
{
	int		start;
	int		count;
	int		i;

	start = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0' && count < len)
	{
		if (str[i] == '\"' && ft_backslash_check(str, i) % 2 == 0)
			ft_skip_quotes(str, &i, DQ);
		else if (str[i] == '\'' && ft_backslash_check(str, i) % 2 == 0)
			ft_skip_quotes(str, &i, SQ);
		else
			i = i + 1;
		if (str[i] == ';' && ft_backslash_check(str, i) % 2 == 0 &&
		str[i + 1] != '\0')
		{
			prompts[count] = ft_substr(str, start, i - start);
			start = i + 1;
			count++;
		}
	}
	prompts[count] = ft_substr(str, start, i - start);
	return (prompts);
}

char		**ft_get_prompts(char *str)
{
	int		len;
	char	**prompts;

	len = ft_count_prompts(str);
	prompts = (char **)malloc(sizeof(char *) * (len + 1));
	if (!prompts)
		ft_malloc_fail();
	prompts[len] = (char *)0;
	prompts = ft_fill_prompts(prompts, str, len);
	return (prompts);
}