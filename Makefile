# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmurray <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 00:13:00 by kmurray           #+#    #+#              #
#    Updated: 2017/07/18 23:28:05 by kmurray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), test, clean, fclean, re

NAME= ft_select

CC= gcc

CFLAGS+= -Wall -Wextra -Werror
TERMFLAGS+= -ltermcap

SRC_PATH= src/
INC_PATH= includes/
OBJ_PATH= obj/
LIBFT_PATH= includes/libft/

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
INC_LFT = $(addprefix -I, $(addprefix $(LIBFT_PATH), $(INC_PATH)))

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_NAME = main.c sl_list.c sl_build_selected.c sl_printfree.c sl_tty.c\
		   sl_signals.c sl_globals.c

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft $(TERMFLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) $(INC_LFT) -o $@ -c $< 

test: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft $(TERMFLAGS)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all
