# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mploux <mploux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/06 18:10:48 by mploux            #+#    #+#              #
#    Updated: 2018/01/06 18:32:50 by mploux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
CC = gcc
FILES =\
main.c

SRC = srcs/
DIRS = bin

SYSTEM = $(shell uname -s)

WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

OBJS = $(addprefix bin/,$(FILES:.c=.o))

DEPS = -L deps/glfw/build/src/
INCLUDES = -I includes/ -I deps/glfw/include/

DEPSFLAGS = -lglfw3 -framework Cocoa -framework OpenGL\
				-framework IOKit -framework CoreVideo

CFLAGS = -Wall -Wextra
FLAGS = $(CFLAGS) $(INCLUDES)

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

$(NAME): $(DIRS) $(OBJS)
	@printf "\r$(GREEN)Compiling sources: DONE !                      $(NO_COLOR)\n";

	@printf "Building libGLFW...\r"
	@$(MKDIR) deps/glfw/build > /dev/null
	@cd deps/glfw/build && cmake .. > /dev/null
	@make -C deps/glfw/build/ > /dev/null
	@printf "\r$(GREEN)Building libGLFW: DONE !$(NO_COLOR)\n";

	@printf "Building objects...\r"
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(DEPS) $(DEPSFLAGS)
	@printf "\r$(GREEN)Building objects: DONE !$(NO_COLOR)\n";
	@printf "\n$(GREEN)Building done: $(GREEN_BG)$(NAME)$(NO_COLOR)\n"

$(DIRS):
	@$(MKDIR) $(dir $(OBJS))

bin/%.o: srcs/%.c
	@printf "\rCompiling sources: $^                          \r";
	@$(CC) -MMD -c $^ -o $@ $(CFLAGS) $(INCLUDES)

.PHONY: all clean clean-libs fclean-libs fclean re

all: $(NAME)

clean:
	@printf "Cleaning objects..."
	@$(RMDIR) bin
	@printf "\r$(GREEN)Cleaning objects: DONE !$(NO_COLOR)\n";

clean-libs: clean
	@printf "Cleaning libGLFW..."
	@$(RMDIR) deps/glfw/build
	@printf "\r$(GREEN)Cleaning libGLFW: DONE !$(NO_COLOR)\n";

fclean-libs: clean-libs
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
