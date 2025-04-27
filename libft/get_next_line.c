/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 08:21:08 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 18:27:17 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_full_line(int fd, char *stock, char *buffer)
{
	int		i;
	char	*temp;

	i = 1;
	if (!stock)
		stock = ft_strdup("");
	if (!stock)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1 || (i == 0 && ft_strlen(stock) == 0))
			return (free(stock), NULL);
		buffer[i] = 0;
		temp = stock;
		stock = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n') || buffer[0] == '\n')
			break ;
	}
	return (stock);
}

char	*store_static_var(char *value)
{
	int		i;
	char	*stock;

	i = 0;
	stock = NULL;
	if (value == NULL)
		return (stock);
	while (value[i] != '\n' && value[i] != '\0')
		i++;
	if (value[i] == '\n')
	{
		stock = ft_substr(value, i + 1, ft_strlen(value) - i);
		value[i + 1] = 0;
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*buffer;
	char		*return_value;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stock)
		{
			free(stock);
			stock = NULL;
		}
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	return_value = get_full_line(fd, stock, buffer);
	free(buffer);
	buffer = NULL;
	stock = store_static_var(return_value);
	return (return_value);
}
