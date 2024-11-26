SRCS := $(shell find . -name "*.cpp")
NAME := ircserv
CXXFLAGS := 
# -Wall -Wextra -Werror -std=c++98
CXX = c++
SANITIZE = -fsanitize=address -g

OBJS  = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(SANITIZE)
$(NAME):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SANITIZE)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re