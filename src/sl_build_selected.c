/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_build_selected.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 20:23:50 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/12 20:52:35 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	sl_build_selected(t_select *select)
{
	t_arglist	*scout;
	int			n;

	scout = select->head;
	n = scout->hl ? 1 : 0 ;
	scout = scout->next;
	while (scout->next && scout != select->head)
	{
		n = scout->hl ? n + 1 : n ;
		scout = scout->next;
	}
	select->selected = ft_memalloc(sizeof(char *) * (n + 1));
	select->selected[n] = NULL;
	if (scout->hl && n-- > 0)
		select->selected[n] = ft_strdup(scout->li);
	scout = scout->prev;
	while (scout->prev && scout != select->head)
	{
		if (scout->hl)
			select->selected[--n] = ft_strdup(scout->li);
		scout = scout->prev;
	}
}
