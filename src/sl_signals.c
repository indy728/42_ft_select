/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 22:24:52 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/18 23:24:56 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static void	sl_sigtstp(t_select *select)
{
	char		susp[2];

	sl_tty_reset();
	susp[0] = select->tty.c_cc[VSUSP];
	susp[1] = 0;
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, susp);
}

static void	sl_sigcont(t_select *select)
{
	sl_tty_init();
	sl_putenvstr(CLEAR_WINDOW);
	sl_lstprint(select, select->head);
	signal(SIGCONT, SIG_DFL);
}

static void	sl_sigwinch(t_select *select)
{
	sl_getwinsize();
	sl_putenvstr(CLEAR_WINDOW);
	if (select->winx < select->col_max)
	{
		ft_putendl_fd(RED""BOLD"TOO SMALL!"RESET, 2);
	}
	else
		sl_lstprint(select, select->head);
}

static void	sl_sighandles(int sig)
{
	t_select	*select;

	if (sig == SIGINT || sig == SIGQUIT || sig == SIGKILL || sig == SIGTERM)
	{
		sl_tty_reset();
		sl_free_select();
		exit(1);
	}
	select = get_select_address();
	if (sig == SIGWINCH)
		sl_sigwinch(select);
	if (sig == SIGTSTP)
		sl_sigtstp(select);
	if (sig == SIGCONT)
		sl_sigcont(select);
}

void		sl_signals(void)
{
	signal(SIGTERM, sl_sighandles);
	signal(SIGINT, sl_sighandles);
	signal(SIGQUIT, sl_sighandles);
	signal(SIGKILL, sl_sighandles);
	signal(SIGTSTP, sl_sighandles);
	signal(SIGWINCH, sl_sighandles);
	signal(SIGCONT, sl_sighandles);
}
