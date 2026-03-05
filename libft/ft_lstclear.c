/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:52:54 by msnizek           #+#    #+#             */
/*   Updated: 2025/06/02 19:09:02 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*actual;

	if (!lst || !del)
		return ;
	actual = *lst;
	while (actual)
	{
		next = actual->next;
		del(actual->content);
		free(actual);
		actual = NULL;
		actual = next;
	}
	*lst = NULL;
}
