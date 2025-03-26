/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:55:35 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:55:36 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memo_free(char **tab, int nbrword)
{
	while (nbrword >= 0)
	{
		free(tab[nbrword]);
		nbrword -= 1;
	}
	free(tab);
}

static int	ft_countword(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static size_t	len_word(char *s, char c, int *pos)
{
	size_t	j;

	j = 0;
	while (s[*pos] == c)
		*pos += 1;
	while (s[*pos + j] && s[*pos + j] != c)
		j++;
	*pos += j;
	while (s[*pos] == c)
		*pos += 1;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char			**value;
	unsigned int	i;
	unsigned int	start;
	size_t			len;
	int				nbrword;

	i = 0;
	len = 0;
	nbrword = ft_countword(s, c);
	value = (char **)malloc(sizeof(char *) * (nbrword + 1));
	if (!value)
		return (NULL);
	while (s[len] == c)
		len++;
	while ((int) i < nbrword)
	{
		start = (unsigned int) len;
		value[i] = ft_substr(s, start,
				len_word((char *) s, c, (int *) &len));
		if (!value[i])
			return (memo_free(value, i), NULL);
		i++;
	}
	value[i] = NULL;
	return (value);
}
