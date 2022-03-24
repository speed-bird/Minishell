/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:10:43 by jrobert           #+#    #+#             */
/*   Updated: 2022/03/16 19:01:02 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_tknlst(t_token **head, void (*del)(void *))
{
	t_token	*temp;
	t_token	*ptr;

	if (!head || !del)
		return ;
	ptr = NULL;
	temp = *head;
	while (temp)
	{
		(*del)(temp->content);
		ptr = temp;
		temp = temp->next;
		free(ptr);
	}
	*head = NULL;
}

int	free_all(t_token **head)
{
	clear_tknlst(head, free);
	return (0);
}

int	fail(char *err)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putendl_fd(err, 2);
	return (0);
}
