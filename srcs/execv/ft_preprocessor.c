/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_preprocessor.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 17:07:55 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/08 19:36:38 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int			ft_count_paths(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ':')
			count++;
		i++;
	}
	return (count);
}

static void			ft_add_cmd(char **pathcmd, char *cmd)
{
	char	*newcmd;
	char	*tmp;
	int		i;

	i = 0;
	newcmd = ft_strjoin("/", cmd);
	while (pathcmd[i] != (char *)0)
	{
		tmp = gnl_strjoin(pathcmd[i], newcmd);
		pathcmd[i] = tmp;
		i++;
	}
	free(newcmd);
}

static char			**fill_path(char **pathcmd, char *str)
{
	int		start;
	int		i;
	int		j;
	
	start = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ':')
		{
			pathcmd[j] = ft_substr(str, start, i - start);
			j++;
			start = i + 1;
		}
		i++;
	}
	pathcmd[j] = ft_substr(str, start, i - start);
	return (pathcmd);
}

char				**ft_path_array(char *str, char *cmd)
{
	int		count;
	char	**pathcmd;

	count = ft_count_paths(str);
	pathcmd = (char **)malloc(sizeof(char *) * (count + 2));
	if (!pathcmd)
		ft_malloc_fail();
	pathcmd[count + 1] = (char *)0;
	pathcmd = fill_path(pathcmd, str);
	free(str);
	ft_add_cmd(pathcmd, cmd);
	return (pathcmd);
}
