/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotations_parser.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 20:52:54 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/20 18:55:31 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_charjoin(char *str, char c)
{
	int		len;
	char	*newstr;
	int		i;

	len = ft_strlen(str) + 2;
	newstr = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (str[i] != '\0')
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	return (newstr);
}

void			ft_parse_dollar(char *str, int *i,
						t_trim *trim, t_shell *shell)
{
	char	*tmp;
	char	*new_str;
	char	*old_str;

	if (ft_backslash_check(str, *i) % 2 == 0)
	{
		new_str = ft_substr(str, trim->start, *i - trim->start);
		tmp = ft_find_variable(str, i, shell);
		old_str = gnl_strjoin(new_str, tmp);
		if (trim->res == NULL)
			trim->res = ft_strdup(old_str);
		else
			trim->res = gnl_strjoin(trim->res, old_str);
		trim->start = *i;
		free(tmp);
		free(old_str);
	}
}

void			ft_strspecial(char *str, t_trim *trim, int *i, char c)
{
	char	*new_str;
	char	*old_str;

	old_str = ft_substr(str, trim->start, *i - trim->start);
	if (trim->res)
	{
		new_str = ft_charjoin(old_str, c);
		free(old_str);
		old_str = trim->res;
		trim->res = ft_strjointwo(old_str, new_str);
	}
	else
	{
		new_str = ft_make_single_char_str(c);
		trim->res = ft_strjointwo(old_str, new_str);
	}
	*i = *i + 2;
	trim->start = *i;
	free(old_str);
}

static char		*ft_insert_output(char *str, int i, t_trim *trim)
{
	char *old_str;
	char *output;

	if (trim->res == NULL)
		output = ft_substr(str, trim->start, i - trim->start - 1);
	else
	{
		old_str = ft_substr(str, trim->start, i - trim->start - 1);
		output = ft_strjointwo(trim->res, old_str);
	}
	return (output);
}

char			*ft_doublequotes_str(char *str, int *i, t_shell *shell)
{
	t_trim		trim;
	char		*output;

	trim.res = NULL;
	trim.start = *i + 1;
	*i = *i + 1;
	output = NULL;
	while ((str[*i] != '\"' && str[*i] != '\n' && str[*i] != '\0'))
	{
		if (str[*i] == '$' && !ft_strchr("\\\"", str[*i + 1]))
			ft_parse_dollar(str, i, &trim, shell);
		else if (str[*i] == '\\' && ft_strchr("\\\"", str[*i + 1]))
			ft_strspecial(str, &trim, i, str[*i + 1]);
		else
			*i = *i + 1;
	}
	*i = *i + 1;
	output = ft_insert_output(str, *i, &trim);
	free(trim.res);
	return (output);
}
