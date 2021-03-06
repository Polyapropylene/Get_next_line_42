/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:28:51 by rrhyhorn          #+#    #+#             */
/*   Updated: 2021/12/06 20:28:55 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

static char	*write_line(char *stat)
{
	int		i;
	char	*stroka;

	i = 0;
	while (stat[i] != '\n' && stat[i] != '\0')
		i++;
	stroka = (char *)malloc(sizeof(char) * (i + 2));
	if (!stroka)
		return (NULL);
	ft_strlcpy(stroka, stat, i + 2);
	if (stroka[0] == 0)
	{
		free(stroka);
		return (NULL);
	}
	return (stroka);
}

static char	*new_stat(char *stat)
{
	static char	*newstat;
	int			i;

	i = 0;
	while (stat[i] != '\n' && stat[i] != '\0')
		i++;
	if (stat[i] == '\0')
	{
		free(stat);
		return (NULL);
	}
	newstat = (char *)malloc(sizeof(char) * (ft_strlen(stat) - i + 1));
	if (!newstat)
		return (NULL);
	ft_strlcpy(newstat, stat + i + 1, ft_strlen(stat) - i + 1);
	free(stat);
	return (newstat);
}

static char	*make_stat(char *stat, char *buff, int fd)
{
	int		bwr;
	int		cntrl;
	char	*vrmn;

	bwr = 1;
	cntrl = 0;
	while (cntrl == 0 && bwr != 0)
	{
		bwr = read(fd, buff, BUFFER_SIZE);
		if (bwr == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bwr] = '\0';
		if (!stat)
			stat = ft_strdup("");
		vrmn = stat;
		stat = ft_strjoin(vrmn, buff);
		free(vrmn);
		if (ft_strchr(buff, '\n') != 0)
			cntrl = 1;
	}
	free(buff);
	return (stat);
}

char	*get_next_line(int fd)
{
	char		*newline;
	char		*buff;
	static char	*stat;	

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline = NULL;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(buff);
		return (NULL);
	}
	stat = make_stat(stat, buff, fd);
	if (!stat)
		return (NULL);
	newline = write_line(stat);
	stat = new_stat(stat);
	return (newline);
}

/*#include <fcntl.h>
#include <stdio.h>

int	main ()
{
	int		fd;
	char	*new_line;

	fd = open("text.txt", O_RDONLY);
	new_line = get_next_line(fd);
	printf("%s\n", new_line);
	return (0);
}
*/
