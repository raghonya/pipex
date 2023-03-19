/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:33 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 14:37:37 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	else if (!new)
		return ;
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
