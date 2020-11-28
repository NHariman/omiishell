/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gen_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 03:52:14 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/22 18:29:19 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_rm_endline(char *str)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = ft_substr(str, 0, len - 1);
	return (new);
}

void	ft_find_arg(char *str, int *i)
{
	t_qts	qts;

	ft_set_qts(&qts);
	ft_qt_line(str, &qts, i);
	while (!ft_strchr("$><;| \n\0", str[*i]))
		*i = *i + 1;
	return ;
}

char					*ft_strjointwo(char *s1, char *s2)
{
	char		*strduo;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	strduo = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!strduo)
	{
		free(s2);
		return (NULL);
	}
	while (s1 && i < ft_strlen(s1))
	{
		strduo[i] = s1[i];
		i++;
	}
	while (s2 && j < ft_strlen(s2))
	{
		strduo[i + j] = s2[j];
		j++;
	}
	strduo[i + j] = '\0';
	free(s2);
	return (strduo);
}
