/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:21:00 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 17:21:52 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char **s, int j)
{
	if (!s[j])
		while (--j >= 0)
			free(s[j]);
	return (j + 1);
}

static void	func(const char *s, int *i, int *letcnt, char c)
{
	*letcnt = 0;
	while (s[*i] == c)
		(*i)++;
	while (s[*i] != c && s[*i] != 0)
	{
		(*letcnt)++;
		(*i)++;
	}
}

int	stralloc(char const *s, char **split, int wrdcnt, char c)
{
	int	i;
	int	j;
	int	letcnt;

	i = (!(j = -1));
	while (++j < wrdcnt)
	{
		while (s[i])
		{
			func (s, &i, &letcnt, c);
			if (letcnt)
			{
				split[j] = malloc (sizeof(char) * (letcnt + 1));
				if (!check(split, j))
					return (0);
				break ;
			}
		}
	}
	return (1);
}

static char	**fill(char const *s, char **split, int wrdcnt, char c)
{
	int	i;
	int	j;
	int	let;

	i = 0;
	j = 0;
	while (j < wrdcnt)
	{
		let = 0;
		while (s[i])
		{
			while (s[i] == c)
				i++;
			while (s[i] != c && s[i] != 0)
				split[j][let++] = s[i++];
			split[j][let] = 0;
			break ;
		}
		j++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		wrdcnt;
	char	**split;

	i = 0;
	wrdcnt = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			wrdcnt++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	split = malloc (sizeof(char *) * (wrdcnt + 1));
	if (!split)
		return (NULL);
	if (!stralloc(s, split, wrdcnt, c))
	{
		free (split);
		return (NULL);
	}
	return (fill(s, split, wrdcnt, c));
}

// #include <stdio.h>

// int main()
// {
// 	char c = ' ', s[1000] = "asdhua shaji rguhe e $^&* 890HU 7237 E9 79 a";
// 	char **s1 = ft_split(s, c);
// 	int i = 0, wrdcnt = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i] != 0)
// 			wrdcnt++;
// 		while (s[i] != c && s[i] != 0)
// 			i++;
// 	}
// 	printf ("%d\n", wrdcnt);
// 	i = 0;
// 	while (i < wrdcnt + 1)
// 	{
// 		printf ("%s ,", s1[i]);
// 		i++;
// 	}
// }
