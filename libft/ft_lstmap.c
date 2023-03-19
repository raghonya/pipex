/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:58 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 14:35:12 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*a;

	a = NULL;
	while (lst)
	{
		new = ft_lstnew (f(lst->content));
		if (!new)
		{
			ft_lstclear (&new, del);
			return (NULL);
		}
		ft_lstadd_back(&a, new);
		lst = lst->next;
	}
	return (a);
}

// int main()
// {
// 	t_list * head = NULL;
// 	head = (t_list *) malloc(sizeof(t_list));
// 	head->content = "1";
// 	head->next = (t_list *) malloc(sizeof(t_list));
// 	head->next->content = "2";
// 	head->next->next = malloc(sizeof(t_list));
// 	head->next->next->content = "3";
// 	head->next->next->next = malloc(sizeof(t_list));
// 	head->next->next->next->content = "AASFDGASDG";
// 	head->next->next->next->next = NULL;
// 	t_list *s = ft_lstmap (head, NULL, NULL);
// 	printf ("%s\n", s->content);
// }
