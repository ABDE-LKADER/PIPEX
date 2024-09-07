#***************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 17:23:22 by abadouab          #+#    #+#              #
#    Updated: 2024/05/14 23:10:09 by abadouab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
SRCS		=	pipex.c execute.c
HEADER		=	pipex.h

OBJS		=	$(SRCS:.c=.o)
MYLB		=	MYLIB
MYAR		=	MYLIB/libar.a

FLAGS		=	cc -Wall -Wextra -Werror
RM			=	rm -fr

GREEN		=	"\033[1;32m"
YELOW 		=	"\033[1;33m"
REDCL 		=	"\033[1;31m"
RESET 		=	"\033[0m"

all: start $(MYLB) $(NAME) finish

start:
	@printf "\n"
	@echo $(GREEN)"Starting build..."
	@sleep 1
	@printf "Loading [ "

finish:
	@echo $(GREEN) ] 100%$(RESET)
	@echo $(GREEN)Project built.$(RESET)
	@printf "\n"

$(MYLB):
	@make -C $(MYLB) --no-print-directory

$(NAME): $(OBJS)
	@$(FLAGS) $^ -L $(MYLB) -l ar -o $(NAME)

$(OBJS): %.o: %.c $(HEADER) $(MYAR)
	@$(FLAGS) -c -I $(MYLB) $< -o $@
	@printf $(GREEN)"."$(RESET)

clean:
	@$(RM) $(OBJS)
	@make clean -C $(MYLB) --no-print-directory
	@echo $(YELOW)Cleaning up 🧹💫$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(MYLB) --no-print-directory
	@echo $(REDCL)Purging all files 🗑️$(RESET)

re: fclean all

.PHONY: $(MYLB)
