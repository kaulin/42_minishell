# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:32:02 by kkauhane          #+#    #+#              #
#    Updated: 2024/05/10 15:54:14 by kkauhane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Check if readline library is installed on Linux or Mac, if not show message
CURRENT_OS = $(uname -s)
ifeq ($(CURRENT_OS), Linux)
check_readline:
	@test -f /usr/include/readline/readline.h || { echo "Readline library \ 
		not found. Please install it using the following command:"; \
		echo "sudo apt-get install make libreadline-dev"; \
		exit 1; }
else ifeq ($(CURRENT_OS), Darwin)
	READLINE_DIR := $(shell if [ -d ~/.brew/opt/readline ]; then \
		echo ~/.brew/opt/readline; \
		else if [ -d /usr/local/opt/readline ]; \
		then echo /usr/local/opt/readline; \
		else echo "Readline library not found. Please install it via"; \
			echo "brew install readline"; \
			exit 1; \
		fi; fi)
	INCS = -I $(READLINE_DIR)/include
	LIBS = -L $(READLINE_DIR)/lib
endif

NAME		= minishell
CFLAGS		= -Wextra -Wall -Werror
LIBFTNAME	= libft.a
LIBFTDIR 	= ./libft

SRCS	:= main.c
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

libft:
	@make -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) -o $(INCS) $(LIBS) $(NAME) $(OBJS) -L$(LIBFTDIR) -lft -lreadline -o $@

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFTDIR) fclean

re: clean all

.PHONY: all, clean, fclean, re, libft