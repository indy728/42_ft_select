/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_build_selected.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 20:23:50 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/18 23:20:37 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static int	get_arr_size(t_select *select)
{
	t_arglist	*scout;
	int			n;

	scout = select->head;
	n = scout->hl ? 1 : 0;
	scout = scout->next;
	while (scout && scout->next && scout != select->head)
	{
		n = scout->hl ? n + 1 : n;
		scout = scout->next;
	}
	return (n);
}

void		sl_build_selected(t_select *select)
{
	t_arglist	*scout;
	int			n;
	int			i;

	n = get_arr_size(select);
	scout = select->head;
	i = -1;
	select->selected = ft_memalloc(sizeof(char *) * (n + 1));
	select->selected[n] = NULL;
	if (scout->hl && ++i < n)
		select->selected[i] = ft_strdup(scout->li);
	scout = scout->next;
	while (scout && scout->next && scout != select->head)
	{
		if (scout->hl)
			select->selected[++i] = ft_strdup(scout->li);
		scout = scout->next;
	}
}
