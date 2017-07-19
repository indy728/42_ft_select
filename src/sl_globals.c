/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_globals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 23:25:34 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/18 23:29:45 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int			sl_putchar(int c)
{
	return (write(2, &c, 1));
}

void		sl_putenvstr(char *str)
{
	char	tmp[3];

	ft_bzero(tmp, 3);
	tputs(tgetstr(ft_strncpy(tmp, str, 2), NULL), 1, sl_putchar);
}

t_select	*get_select_address(void)
{
	static t_select	*select;

	if (!select)
	{
		if (!(select = ft_memalloc(sizeof(t_select))))
			ft_exit_malloc_error("Error allocating memory", sizeof(t_select));
	}
	return (select);
}

void		sl_tty_init(void)
{
	t_select	*select;

	select = get_select_address();
	if ((tgetent(NULL, getenv("TERM"))) < 1
			|| (tcgetattr(0, &select->tty) == -1))
	{
		ft_printf(TTY_FGET);
		free(select);
		exit(1);
	}
	select->tty.c_lflag &= ~(ICANON | ECHO);
	select->tty.c_cc[VMIN] = 1;
	select->tty.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &(select->tty)) == -1)
	{
		ft_printf(TTY_FSET);
		sl_free_select();
		exit(1);
	}
	sl_putenvstr(TERM_INIT);
	sl_putenvstr(HIDE_CURSOR);
}

void		sl_tty_reset(void)
{
	t_select	*select;

	select = get_select_address();
	select->tty.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &(select->tty));
	sl_putenvstr(CLEAR_WINDOW);
	sl_putenvstr(RESET_TERM);
	sl_putenvstr(SHOW_CURSOR);
}
