/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:03:20 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:51:46 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nv;

	nv = malloc(sizeof(t_list));
	if (!nv)
		return (NULL);
	nv->content = content;
	nv->next = NULL;
	return (nv);
}
