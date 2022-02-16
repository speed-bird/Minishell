/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:10:47 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 19:39:32 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ref;

	if (!alst)
		return ;
	ref = *alst;
	if (*alst)
	{
		while (ref->next)
			ref = ref->next;
		ref->next = new;
	}
	else
		*alst = new;
}
