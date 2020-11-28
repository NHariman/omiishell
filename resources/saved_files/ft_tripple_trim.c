/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tripple_trim.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 21:12:40 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/05 22:35:53 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_printf("----ERROR START---\n");
// ft_printf("----ERROR END---\n");

#include "../minishell.h"
#include <stdio.h>

void			set_trim(t_struct_em *trim)
{
	trim->begin = 0;
	trim->end = 0;
	trim->single = 0;
	trim->doubble = 0;
}

void   ft_split_begin(t_struct_em *trim, char *str)
{
	int	i;

	i = 0;
	trim->s_begin = (char *)malloc((trim->begin + 1) * sizeof(char));
	if (!trim->s_begin)
		return ;
	while (i < trim->begin)
	{
		trim->s_begin[i] = str[i];
		i++;
	}
	trim->s_begin[i] = '\0';
}

void   ft_split_end(t_struct_em *trim, char *str)
{
	int	i;

	i = ft_strlen(str);
	trim->s_end = (char *)malloc((i - trim->begin) * sizeof(char));
	if (!trim->s_end)
		return ;
	i = 0;
	trim->end = trim->begin;
	while (str[i])
	{
		trim->s_end[i] = trim->str[trim->end];
		trim->end++;
		i++;
	}
	trim->s_end[i] = '\0';
}

int		ft_stop_split(t_struct_em *trim, char *str)
{
	trim->begin--;
	if (str[trim->begin] == '\\')
	{
		ft_split_begin(trim, str);
		ft_split_end(trim, str);
		trim->s_cache = ft_strjoin(trim->s_begin, trim->s_end);
		free(trim->s_begin);
		free(trim->s_end);
		return (1);
	}
	else
	{
		trim->begin++;
		return (0);
	}
}

void	ft_variable(t_struct_em *trim, char *str)
{
	int len;
	int	end;//len of variable in the str so $PAT
	char *var;
	int		error;

	error = 0;
	len = 0;
	end = trim->begin;//start at the $
	while (str[end] && str[end] != '\n' && str[end] != ' ')
		len++;
	var = ft_substr(str, trim->begin, len);
	ft_printf("variable == [%s]\n", var);
	error = ft_search_variable(trim, var);
	//if error == 1
}

void   ft_tripple_trim(t_struct_m *echo)
{
	t_struct_em trim;

	set_trim(&trim);
	trim.begin = 0;
	while (echo->str[trim.begin] && echo->str[trim.begin] != '\n')
	{
		if (echo->str[trim.begin] == '$')
		{
			if (ft_stop_split(&trim, echo->str) == 1)//backslash
			{
				free(echo->str);
				echo->str = ft_strdup(trim.s_cache);
				free(trim.s_cache);
				printf("backslash[%s]", echo->str);
			}
			else//no backslash
			{
				ft_split_begin(&trim, echo->str);
				ft_printf("begin == [%s]\n", trim.s_begin);
				ft_variable(&trim, echo->str);
				trim.s_cache = ft_strjoin(trim.s_begin, trim.s_end);
				trim.begin = ft_strlen(trim.s_cache);
				free(trim.s_begin);
				free(trim.s_end);
				ft_split_end(&trim, echo->str);
				free(echo->str);
				echo->str = ft_strjoin(trim.s_cache, trim.s_end);
				free(trim.s_end);
				free(trim.s_cache);
			}
		}
		trim.begin++;
	}
	//remove the empty lines at the end of the string
}
