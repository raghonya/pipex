/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:03:43 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:45 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	s1len;
	size_t	s2len;
	char	*s;

	i = 0;
	k = 0;
	s1len = gnl_strlen(s1);
	s2len = gnl_strlen(s2);
	s = malloc(s1len + s2len + 1);
	if (!s)
		return (NULL);
	while (i < s1len + s2len)
	{
		if (i < s1len)
			s[i] = s1[i];
		else
			s[i] = s2[k++];
		i++;
	}
	s[i] = 0;
	return (s);
}

char	*gnl_strdup(const char *s)
{
	size_t	i;
	size_t	slen;
	char	*dup;

	i = 0;
	slen = gnl_strlen(s);
	dup = malloc((sizeof(char) * (slen + 1)));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
