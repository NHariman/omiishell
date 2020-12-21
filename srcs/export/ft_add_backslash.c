/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_add_backslash.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 02:42:17 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/08 22:40:22 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			ft_add_backslash(t_trim *trim, char *str, int *i)
{
	char	*newstr;
	char	*tmp;

	newstr = ft_substr(str, trim->start, *i - trim->start);
	tmp = ft_charjoin(newstr, '\\');
	if (trim->res == NULL)
		trim->res = ft_strdup(tmp);
	else
	{
		newstr = gnl_strjoin(trim->res, tmp);
		trim->start = *i;
		trim->res = ft_strdup(newstr);
	}
	*i = *i + 1;
	free(newstr);
	free(tmp);
}

static char		*ft_add_output(char *str, int i, t_trim *trim)
{
	char	*output;
	char	*old_str;
	char	*new_str;

	old_str = NULL;
	new_str = ft_substr(str, trim->start, i - trim->start);
	if (trim->res == NULL)
		output = ft_strdup(new_str);
	else
	{
		old_str = ft_strdup(trim->res);
		output = ft_strjoin(old_str, new_str);
		free(old_str);
	}
	free(new_str);
	return (output);
}

static char		*ft_parse_value(char *str)
{
	t_trim	trim;
	int		i;
	char	*output;

	trim.res = NULL;
	trim.start = 0;
	i = 0;
	output = NULL;
	while (str[i] != '\0')
	{
		if (ft_strchr("$\"\\", str[i]))
			ft_add_backslash(&trim, str, &i);
		i++;
	}
	output = ft_add_output(str, i, &trim);
	free(str);
	free(trim.res);
	return (output);
}

char			*ft_add_quotations(char *str, int start)
{
	char	*tmp;
	char	*value;

	tmp = ft_substr(str, start, ft_strlen(str) - start);
	value = ft_parse_value(tmp);
	tmp = ft_strjointwo("\"", value);
	value = gnl_strjoin(tmp, "\"");
	return (value);
}
