/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrinaldi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:37:26 by nrinaldi          #+#    #+#             */
/*   Updated: 2024/04/09 12:38:06 by nrinaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!*s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

//i need to use a representation of ft_substr in libft for this
char	*ft_splitstr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*splitstr;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	splitstr = malloc(sizeof(char) * (len + 1));
	if (!splitstr)
		return (NULL);
	while (i < len)
	{
		splitstr[i] = s[start];
		i++;
		start++;
	}
	splitstr[i] = '\0';
	return (splitstr);
}

void	ft_freesplit(char **list)
{
	size_t	i;

	i = 0;
	if (list == NULL)
		return ;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	len;
	size_t	i;
	size_t	j;

	list = (char **)malloc(sizeof (char *) * (countwords(s, c) + 1));
	i = 0;
	j = 0;
	if (!list || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
		{
			len = 0;
			while (s[i + len] != c && s[i + len] != '\0')
				len++;
			list[j++] = ft_splitstr(s + i, 0, len);
			i += len;
		}
	}
	list[j] = NULL;
	return (list);
}
