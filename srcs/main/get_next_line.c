/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 17:14:10 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/14 17:27:59 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char					*gnl_strjoin(char *s1, char *s2)
{
	char		*strduo;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	strduo = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!strduo)
	{
		free(s1);
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
	free(s1);
	return (strduo);
}

static int				find_newline(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char				*read_line(t_gnl gnl)
{
	char		buf[1000 + 1];
	char		*tmp;

	gnl.bytes_read = 1;
	while (gnl.bytes_read > 0)
	{
		gnl.bytes_read = read(gnl.fd, buf, 1000);
		if (gnl.bytes_read < 0)
			return (NULL);
		buf[gnl.bytes_read] = '\0';
		if (!gnl.line_read)
			gnl.line_read = ft_strdup(buf);
		else
		{
			tmp = gnl_strjoin(gnl.line_read, buf);
			gnl.line_read = (!tmp ? NULL : ft_strdup(tmp));
			free(tmp);
		}
		if (!gnl.line_read)
			return (NULL);
		if (find_newline(gnl.line_read) || gnl.line_read[0] == '\n')
			break ;
	}
	return (gnl.line_read);
}

static int				fill_line(t_gnl gnl, char **line)
{
	*line = ft_strdup(gnl.line_read);
	if (!*line)
		return (-1);
	return (1);
}

int						get_next_line(int fd, char **line)
{
	t_gnl			gnl;
	int				ret;

	ret = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	gnl.line_read = NULL;
	gnl.fd = fd;
	*line = gnl.line_read;
	gnl.line_read = read_line(gnl);
	if (!gnl.line_read)
		return (-1);
	ret = fill_line(gnl, line);
	free(gnl.line_read);
	return (ret);
}
