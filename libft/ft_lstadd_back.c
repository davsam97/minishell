/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:40:48 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:50:07 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *nv)
{
	t_list	*last;

	if (!lst || !nv)
		return ;
	if (!*lst)
	{
		*lst = nv;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = nv;
}
