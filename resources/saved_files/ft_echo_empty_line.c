/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo_empty_line.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 21:09:41 by anonymous     #+#    #+#                 */
/*   Updated: 2020/11/07 14:23:15 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_printf("----ERROR START---\n");
// ft_printf("----ERROR END---\n");

#include "../minishell.h"
#include <stdio.h>

static void			set_empty(t_struct_e *empty)
{
	empty->begin = 0;
	empty->end = 0;
	empty->single = 0;
	empty->doubble = 0;
}

static void		ft_cut_begin(t_struct_e *empty, char *str)
{
	int		i;

	i = 0;
	empty->begin++;
	empty->s_begin = (char *)malloc((empty->begin + 1) * sizeof(char));
	while (i < empty->begin)
	{
		empty->s_begin[i] = str[i];
		i++;
	}
	empty->s_begin[i] = '\0';
}

static void		ft_cut_end(t_struct_e *empty, char *str)
{
	int		i;

	i = ft_strlen(str);
	empty->s_end = (char *)malloc((i - empty->end + 1) * sizeof(char));
	i = 0;
	while (str[empty->end])
	{
		empty->s_end[i] = str[i];
		i++;
		empty->end++;
	}
	empty->s_end[i] = '\0';
}

static void		ft_empty_line_loop_cut(t_struct_e *empty, char *str)
{
	empty->end = empty->begin;
	ft_printf("begin == %i\n", empty->begin);
	while (str[empty->end] == ' ')
	{
		empty->end++;
	}
	ft_printf("end == %i\n", empty->end);
	if (empty->end - empty->begin == 1)
	{
		return ;
	}
	else if (empty->begin < empty->end)
	{
		ft_cut_begin(empty, str);
		ft_cut_end(empty, str);
		empty->s_cache = ft_strjoin(empty->s_begin, empty->s_end);
		free(empty->s_begin);
		free(empty->s_end);
	}
}

char			*ft_echo_empty_line(char *str)
{
	t_struct_e empty;

	set_empty(&empty);
	while (str[empty.begin] && str[empty.begin] != '\n')
	{
		if (str[empty.begin] == '\"' && empty.single == 0 && empty.doubble == 0)
			empty.doubble = 1;
		else if (str[empty.begin] == '\'' && empty.single == 0 && empty.doubble == 0)
			empty.doubble = 1;
		else if (str[empty.begin] == '\"' && empty.doubble == 1)
			empty.doubble = 0;
		else if (str[empty.begin] == '\'' && empty.single == 1)
			empty.doubble = 0;
		else if (str[empty.begin] == ' ' && empty.single == 0 && empty.doubble == 0)
		{
			ft_empty_line_loop_cut(&empty, str);
			free(str);
			str = ft_strdup(empty.s_cache);
			free(empty.s_cache);
			printf("[%i][%c]\n", empty.begin, str[empty.begin]);
		}
		empty.begin++;
	}
	printf("str == [%s]\n", str);
	return (str);
}
