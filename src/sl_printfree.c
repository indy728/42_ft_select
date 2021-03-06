/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_printfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 20:39:47 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/18 21:16:02 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	sl_print_selected(t_select *select)
{
	int	i;

	i = -1;
	if (!select->selected)
		return ;
	while (++i < ft_size_r(select->selected) - 1)
		ft_printf("%s ", select->selected[i]);
	ft_putendl(select->selected[i]);
}

void	sl_free_select(void)
{
	t_select	*select;

	select = get_select_address();
	sl_print_selected(select);
	sl_lstdel(&select->head);
	ft_del_r(select->selected);
	free(select);
}
