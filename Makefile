# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 13:17:58 by lseema            #+#    #+#              #
#    Updated: 2021/01/15 22:04:48 by lseema           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 := corewar

DIR_SRCS	 := srcs/
DIR_INCLUDES := includes/
DIR_BIN		 := bin/
DIR_LFT		 := libft/
LIBFT		 := libft.a
HEADERS		 := corewar.h libft.h op.h error.h
CC			 := gcc
FLAGS		 := -Wall -Wextra -Werror -g
RM			 := /bin/rm -rf
SRCS		 := corewar.c\
				parse.c\
				parse_code.c\
				player.c\
				vm.c\
				carrage.c\
				arena.c\
				op.c\
				check.c\
				messages.c\
				operations1.c\
				operations2.c\
				operations3.c\
				operations4.c\
				op_validation.c\
				memory_operations.c\
				calc_size.c\
				dump.c\
				free.c

OBJ			 := $(SRCS:.c=.o)
LFT			 := $(addprefix $(DIR_LFT), $(LIBFT))
MAKE_LFT	 := make -C $(DIR_LFT)

vpath %.c $(DIR_SRCS)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDES)

all: make_lft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix $(DIR_BIN), $(OBJ)) $(LFT) -o $@
	@echo "corewar compiled"

$(OBJ): %.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $(FLAGS) $< -o $(DIR_BIN)$@ -I $(DIR_INCLUDES)

$(DIR_BIN):
	mkdir -p $@

make_lft:
	$(MAKE_LFT)
clean:
	$(RM) $(addprefix $(DIR_BIN), $(OBJ))
	$(RM) $(DIR_BIN)
	$(MAKE_LFT) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LFT) fclean

re: fclean all

.PHONY: clean fclean all re make_lft
.SILENT: all clean fclean re make_lft $(NAME) $(OBJ) $(DIR_BIN)
