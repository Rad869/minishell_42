/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:57:06 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:57:07 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	value = NULL;
	j = ft_strlen(s1);
	if (s1 && set)
	{
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		if (i == j)
			return (ft_strdup(""));
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]))
			j--;
		value = (char *) malloc(sizeof(char) * (j - i + 1));
		if (value == NULL)
			return (NULL);
		ft_strlcpy(value, &s1[i], j - i + 1);
	}
	return (value);
}
