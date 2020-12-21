/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_rdin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 18:24:20 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/18 16:56:02 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		*ft_make_str(char **arr)
{
	int		i;
	char	*new_str;
	char	*tmp;

	i = 0;
	new_str = ft_strdup(arr[0]);
	while (arr[i + 1] != (char *)0)
	{
		tmp = gnl_strjoin(new_str, arr[i + 1]);
		new_str = tmp;
		i++;
	}
	if (i > 0)
		new_str = tmp;
	return (new_str);
}

static int		ft_count_rds(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("><", str[i]) && ft_backslash_check(str, i) % 2 == 0)
		{
			ft_skip_rd(str, &i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char		*ft_get_rd(char *str, int *i)
{
	int		start;
	char	*rdstr;

	start = *i;
	while (str[*i] == '>' || str[*i] == '<')
		*i = *i + 1;
	while (str[*i] == ' ')
		*i = *i + 1;
	while (!ft_strchr(" ><", str[*i]) ||
		!(ft_strchr(" ><", str[*i]) && ft_backslash_check(str, *i) % 2 == 0))
		*i = *i + 1;
	rdstr = ft_substr(str, start, *i - start);
	return (rdstr);
}

static char		**ft_fill_rdarr(char *str, char **rdarr, int len)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0' && count < len)
	{
		if (ft_strchr("<>", str[i]) && ft_backslash_check(str, i) % 2 == 0)
		{
			rdarr[count] = ft_get_rd(str, &i);
			count++;
		}
		else
			i++;
	}
	rdarr[count] = (char *)0;
	return (rdarr);
}

char			*ft_get_rdin(char *str)
{
	int		len;
	char	**rdarr;
	char	*rdstr;

	len = ft_count_rds(str);
	if (len == 0)
		return (NULL);
	rdarr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!rdarr)
		ft_malloc_fail();
	rdarr = ft_fill_rdarr(str, rdarr, len);
	rdstr = ft_make_str(rdarr);
	ft_free_array(rdarr, ft_arrlen(rdarr));
	return (rdstr);
}
