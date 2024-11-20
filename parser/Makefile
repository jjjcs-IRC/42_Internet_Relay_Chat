# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 11:20:27 by jjhang            #+#    #+#              #
#    Updated: 2024/11/20 17:50:19 by jaeyeuljhan      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP = c++
CPP_FLAGS = -std=c++98 -Wall -Wextra -Werror -g -fsanitize=address
NAME = parser

SRCS_DIR = ./
OBJ_DIR = obj

SUB_DIR = ./SubParsers/
SUB_FILES = SuperParser.cpp \
			NickParser.cpp \
            PassParser.cpp \
            UserParser.cpp

SRCS_FILES = IrcParser.cpp \
             IrcExceptions.cpp \
             parser_tester.cpp \
             $(addprefix $(SUB_DIR), $(SUB_FILES))

HEADER = ./Include ./Include/SubParsers
HEADER_FLAGS = $(addprefix -I, $(HEADER))

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_FILES:.cpp=.o)))

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CPP) $(CPP_FLAGS) -o $(NAME) $^ $(HEADER_FLAGS)
	@echo ✅[$(NAME)] has been built

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.cpp | $(OBJ_DIR)
	@$(CPP) $(CPP_FLAGS) -c -o $@ $< $(HEADER_FLAGS)

$(OBJ_DIR)/%.o : $(SUB_DIR)%.cpp | $(OBJ_DIR)
	@$(CPP) $(CPP_FLAGS) -c -o $@ $< $(HEADER_FLAGS)

$(OBJ_DIR) :
	@mkdir -p $@

clean :
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
