/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:18:10 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 16:18:17 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	k;
	int		j;

	i = 0;
	if ((!str ^ !to_find) && !n)
		return (NULL);
	if (*to_find == 0)
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = -1;
		if (str[i] == to_find[0])
		{
			k = i;
			while (to_find[++j] && str[k] && str[k] == to_find[j] && k < n)
				k++;
			if (!(to_find[j]))
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
