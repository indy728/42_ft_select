/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_tty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 18:19:49 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/18 23:24:38 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static void	li_home(t_select *select, unsigned int event, t_arglist *scout)
{
	if (!scout->next)
		return ;
	scout->ul = 0;
	if (event == HOME)
		select->head->ul = 1;
	else
		select->head->prev->ul = 1;
}

static void	li_del(t_select *select, t_arglist *scout)
{
	if (scout->next)
		scout->next->ul = 1;
	sl_lstpop(&select->head, scout->key);
	select->ct_li--;
	if (!select->ct_li)
	{
		select->head = NULL;
		select->col_max = 0;
	}
	else
		sl_getcolmax(select);
}

static void	arrow(unsigned int event, t_arglist *scout)
{
	if (!scout->next)
		return ;
	scout->ul = 0;
	if (event == DOWN)
		scout->next->ul = 1;
	else
		scout->prev->ul = 1;
}

t_bool		sl_tty(t_select *select)
{
	char			buff[4];
	unsigned int	event;
	t_arglist		*scout;

	sl_lstprint(select, select->head);
	scout = select->head;
	while (!scout->ul && scout->next)
		scout = scout->next;
	ft_bzero(buff, 4);
	read(0, buff, 4);
	event = *(unsigned int *)buff;
	if (event == UP || event == DOWN)
		arrow(event, scout);
	else if (event == SPACE)
		ft_tboolswitch(&scout->hl);
	else if (event == DEL || event == BSPACE)
		li_del(select, scout);
	else if (event == HOME || event == END)
		li_home(select, event, scout);
	else if (event == RETURN)
		sl_build_selected(select);
	return ((event == ESC || event == RETURN) ? 0 : 1);
}
