/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:57:14 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:57:15 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstring(char const *s, unsigned int start, size_t len)
{
	size_t	slen;

	slen = ft_strlen((char *) s);
	if (start >= slen)
		return (1);
	if (len < slen - start)
		return ((int)(len + 1));
	return ((int)(slen - start + 1));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*value;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	value = (char *) malloc(sizeof(*s) * ft_countstring(s, start, len));
	if (value == 0)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			value[j] = s[i];
			j++;
		}
		i++;
	}
	value[j] = 0;
	return (value);
}
