# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2024/10/31 11:20:27 by jjhang            #+#    #+#              #
# #    Updated: 2024/11/20 20:48:23 by jaeyeuljhan      ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# CPP = c++
# CPP_FLAGS = -std=c++98 -Wall -Wextra -Werror -g -fsanitize=address
# LIB_NAME = libparser.a
# AR = ar rcs

# SRCS_DIR = ./
# OBJ_DIR = obj

# SUB_DIR = ./SubParsers/
# SUB_FILES = SuperParser.cpp \
# 			NickParser.cpp \
#             PassParser.cpp \
#             UserParser.cpp

# SRCS_FILES = IrcParser.cpp \
#              IrcExceptions.cpp \
#              $(addprefix $(SUB_DIR), $(SUB_FILES))

# HEADER = ./Include ./Include/SubParsers
# HEADER_FLAGS = $(addprefix -I, $(HEADER))

# OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_FILES:.cpp=.o)))

# all : $(LIB_NAME)  # 아카이브 파일만 만들도록 설정

# $(LIB_NAME): $(OBJS)
# 	@$(AR) $@ $^
# 	@echo ✅[$(LIB_NAME)] has been created

# $(OBJ_DIR)/%.o : $(SRCS_DIR)/%.cpp | $(OBJ_DIR)
# 	@$(CPP) $(CPP_FLAGS) -c -o $@ $< $(HEADER_FLAGS)

# $(OBJ_DIR)/%.o : $(SUB_DIR)%.cpp | $(OBJ_DIR)
# 	@$(CPP) $(CPP_FLAGS) -c -o $@ $< $(HEADER_FLAGS)

# $(OBJ_DIR) :
# 	@mkdir -p $@

# clean :
# 	@rm -f $(OBJS)
# 	@rm -rf $(OBJ_DIR)

# fclean : clean
# 	@rm -f $(LIB_NAME)

# re :
# 	$(MAKE) fclean
# 	$(MAKE) all

# .PHONY : all clean fclean re