/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 19:15:10 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/19 00:17:06 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			sl_getcolmax(t_select *select)
{
	t_arglist		*scout;
	unsigned int	i;

	i = 0;
	scout = select->head;
	while (i++ < select->ct_li)
	{
		select->col_max = ft_max(select->col_max, ft_strlen(scout->li));
		scout = scout->next;
	}
}

void			sl_getwinsize(void)
{
	t_select		*select;
	struct winsize	tty_window;

	select = get_select_address();
	ioctl(0, TIOCGWINSZ, &tty_window);
	select->winx = tty_window.ws_col;
	select->winy = tty_window.ws_row;
}

static t_select	*sl_set_select(int ac, char **av)
{
	int			i;
	t_select	*select;

	i = 0;
	select = get_select_address();
	select->col_max = 0;
	select->ct_li = ac - 1;
	select->head = NULL;
	select->selected = NULL;
	while (++i < ac)
		sl_lstcat(&select->head, sl_lstnew(i, av[i]));
	sl_getcolmax(select);
	return (select);
}

int				main(int ac, char **av)
{
	t_select	*select;
	char		ret;

	if (ac > 1)
	{
		ret = 1;
		sl_tty_init();
		select = sl_set_select(ac, av);
		if (select && select->head)
			select->head->ul = 1;
		while (select->head && ret)
		{
			sl_signals();
			sl_getwinsize();
			sl_putenvstr(CLEAR_WINDOW);
			ret = sl_tty(select);
		}
		sl_tty_reset();
		sl_free_select();
	}
	else
		ft_printf(SL_USAGE);
	return (0);
}
