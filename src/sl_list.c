/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 14:22:36 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/19 14:18:33 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		sl_lstprint(t_select *select, t_arglist *head)
{
	t_arglist				*scout;
	unsigned int			i;

	scout = head;
	if (!scout)
		return ;
	if (select->winx < select->col_max)
		ft_putendl_fd(BLUE""BOLD"!!!!!!!!!!!!"RESET, 2);
	else
	{
		i = -1;
		while (++i < select->ct_li)
		{
			if (scout->ul)
				sl_putenvstr(UNDERLINE);
			if (scout->hl)
				sl_putenvstr(REVERSE_VIDEO);
			ft_putendl_fd(scout->li, 2);
			scout = scout->next;
			sl_putenvstr(EXIT_MODES);
		}
	}
}

void		sl_lstdel(t_arglist **head)
{
	t_arglist	*scout;

	if (!*head)
		return ;
	if (!(*head)->next)
	{
		ft_strdel(&(*head)->li);
		free(*head);
	}
	else
	{
		scout = *head;
		(*head)->prev->next = NULL;
		while (scout->next)
		{
			scout = scout->next;
			ft_strdel(&scout->prev->li);
			free(scout->prev);
		}
		ft_strdel(&scout->li);
		free(scout);
	}
	*head = NULL;
}

void		sl_lstpop(t_arglist **head, int key)
{
	t_arglist	*scout;

	scout = *head;
	while (scout->key != key)
		scout = scout->next;
	if (scout->key == (*head)->key)
	{
		*head = scout->next;
		if (scout->next)
		{
			scout->next->prev = scout->prev;
			scout->prev->next = scout->next;
		}
		ft_strdel(&scout->li);
		free(scout);
	}
	else
	{
		scout->next->prev = scout->prev;
		scout->prev->next = scout->next;
		ft_strdel(&scout->li);
		free(scout);
	}
}

void		sl_lstcat(t_arglist **head, t_arglist *new)
{
	if (!new)
		return ;
	if (*head)
	{
		new->next = *head;
		if ((*head)->prev)
		{
			(*head)->prev->next = new;
			new->prev = (*head)->prev;
		}
		else
		{
			(*head)->next = new;
			new->prev = *head;
		}
		(*head)->prev = new;
	}
	else
		*head = new;
}

t_arglist	*sl_lstnew(int key, char *li)
{
	t_arglist	*new;

	if (!(new = ft_memalloc(sizeof(t_arglist))))
		return (NULL);
	if (!(new->li = ft_strdup(li)))
	{
		free(new);
		return (NULL);
	}
	new->key = key;
	new->ul = 0;
	new->hl = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
