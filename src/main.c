/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 19:15:10 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/13 17:56:25 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int	sl_putchar(int c)
{
	return (write(1, &c, 1));
}

void		sl_getcolmax(t_select *select)
{
	t_arglist		*scout;
	unsigned int	i;

	i = 0;
	scout = select->head;
	while (i++ < select->ct_li)
		select->col_max = ft_max(select->col_max, ft_strlen(scout->li));
}

void		sl_getwinsize(t_select *select)
{
	struct winsize	tty_window;

	ioctl(0, TIOCGWINSZ, &tty_window);
	select->winx = tty_window.ws_col;
	select->winy = tty_window.ws_row;
}

t_select	*tty_init(int ac, char **av)
{
	int			i;
	t_select	*select;

	i = 0;
	if(!(select = ft_memalloc(sizeof(t_select))))
		ft_exit_malloc_error("Error allocating memory", sizeof(t_select));
	if ((tgetent(NULL, getenv("TERM"))) < 1
			|| (tcgetattr(0, &select->tty) == -1))
	{
		ft_printf(TTY_FGET);
		exit(1);;
	}
	select->tty.c_lflag &= ~(ICANON | ECHO);
	select->tty.c_cc[VMIN] = 1;
	select->tty.c_cc[VTIME] = 0;
	select->col_max = 0;
	select->ct_li = ac - 1;
	select->head = NULL;
	select->selected = NULL;
	while (++i < ac)
		sl_lstcat(&select->head, sl_lstnew(i, av[i]));
	sl_getcolmax(select);
	return (select);
}

void		tty_reset(t_select *select)
{
	select->tty.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &(select->tty));
	tputs(tgetstr("te", NULL), 1, sl_putchar);
	tputs(tgetstr("ve", NULL), 1, sl_putchar);
	tputs(tgetstr("cl", NULL), 1, sl_putchar);
	sl_print_selected(select);
	sl_free_select(select);
}

int			main(int ac, char **av)
{
	t_select	*select;
	char		ret;

	if (ac > 1)
	{
		ret = 1;
		select = tty_init(ac, av);
		if (tcsetattr(0, 0, &(select->tty)) == -1)
		{
			ft_printf(TTY_FSET);
			return (1);
		}
		if (select && select->head)
			select->head->ul = 1;
		tputs(tgetstr("vi", NULL), 1, sl_putchar);
		tputs(tgetstr("ti", NULL), 1, sl_putchar);
		while (select->head && ret)
		{
			sl_getwinsize(select);
			tputs(tgetstr("cl", NULL), 1, sl_putchar);
			ret = sl_tty(select);
		}
		tty_reset(select);
		free(select);
	}
	else
		ft_printf(SL_USAGE);
	return (0);
}
