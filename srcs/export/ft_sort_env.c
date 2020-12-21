/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 01:10:02 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/19 01:08:18 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			*ft_order_env(char **env)
{
	int		*order;
	int		len;
	int		i;

	len = ft_arrlen(env);
	order = (int *)ft_calloc(len + 1, sizeof(int));
	order[len] = (int)128;
	i = 0;
	while (i < len)
	{
		order[i] = i;
		i++;
	}
	return (order);
}

void		ft_sort_env(int *order, char **env, int start)
{
	int	len;
	int	i;
	int	tmp;

	len = ft_arrlen(env);
	i = 0;
	tmp = 0;
	if (start == 3)
		return ;
	while (env[i + 1] != (char *)0 && order[i] < 127)
	{
		if (ft_strcmp(env[order[i + 1]], env[order[i]]) < 0)
		{
			tmp = order[i];
			order[i] = order[i + 1];
			order[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
	ft_sort_env(order, env, start + 1);
}
