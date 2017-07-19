/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 00:30:12 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/18 23:19:09 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include "libft.h"

# define TTY_FGET "Terminal failure: error retrieving env terminal type.\n"
# define TTY_FSET "Terminal failure: error setting terminal type.\n"
# define SL_USAGE "./ft_select [arg 0] [arg 1] ... [arg n]\n"
# define ESC		27
# define SPACE		32
# define BSPACE		127
# define END		4610843
# define DEL		2117294875
# define RETURN		10
# define UP			4283163
# define HOME		4741915
# define DOWN		4348699

/*
** Definitions of Terminal Capabilities
*/

# define TERM_INIT		"ti"
# define CLEAR_WINDOW	"cl"
# define STANDOUT_MODE	"so"
# define REVERSE_VIDEO	"mr"
# define UNDERLINE		"us"
# define HIDE_CURSOR	"vi"
# define RESET_TERM		"te"
# define EXIT_STANDOUT	"se"
# define EXIT_MODES		"me"
# define NO_UNDERLINE	"ue"
# define SHOW_CURSOR	"ve"

typedef	struct				s_arglist
{
	int						key;
	char					*li;
	t_bool					ul;
	t_bool					hl;
	struct s_arglist		*next;
	struct s_arglist		*prev;
}							t_arglist;

typedef	struct				s_select
{
	struct termios			tty;
	t_arglist				*head;
	char					**selected;
	unsigned int			col_max;
	unsigned int			ct_li;
	unsigned int			winx;
	unsigned int			winy;

}							t_select;

t_arglist					*sl_lstnew(int key, char *li);
void						sl_lstcat(t_arglist **head, t_arglist *new);
void						sl_lstprint(t_select *select, t_arglist *head);
void						sl_lstpop(t_arglist **head, int key);
void						sl_lstdel(t_arglist **head);
void						sl_build_selected(t_select *select);
void						sl_print_selected(t_select *select);
void						sl_free_select(void);
void						sl_getcolmax(t_select *select);
void						sl_getwinsize(void);
t_bool						sl_tty(t_select *select);
int							sl_putchar(int c);
void						sl_putenvstr(char *str);
t_select					*get_select_address(void);
void						sl_signals(void);
void						sl_tty_reset(void);
void						sl_tty_init(void);

#endif
