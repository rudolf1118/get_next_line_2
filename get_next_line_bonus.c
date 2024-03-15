/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rharutyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:16:05 by rharutyu          #+#    #+#             */
/*   Updated: 2024/03/15 20:16:29 by rharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*new_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	res = malloc(sizeof(char) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n' && str[i])
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

char	*remove_line(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	res = malloc(ft_strlen(str) - i + 1);
	if (!res)
		return (NULL);
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

char	*reader(int fd, char *str)
{
	int		readed;
	char	*res;

	readed = 1;
	res = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!res)
		return (NULL);
	while (readed > 0)
	{
		readed = read(fd, res, BUFFER_SIZE);
		if (readed == -1)
		{
			free(res);
			return (NULL);
		}
		res[readed] = '\0';
		str = ft_joiner(str, res);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(res);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*result[OPEN_MAX];
	char		*newline;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(result[fd]);
		result[fd] = NULL;
		return (NULL);
	}
	result[fd] = reader(fd, result[fd]);
	if (!result[fd])
		return (NULL);
	newline = new_line(result[fd]);
	result[fd] = remove_line(result[fd]);
	if (*newline == '\0')
	{
		free(newline);
		free(result[fd]);
		newline = NULL;
		result[fd] = NULL;
	}
	return (newline);
}
