TARGET = nn_bot
SRC = src/*.cpp
INCLUDES = ./include
CXXFLAGS = -std=c++2a $(addprefix -I,$(INCLUDES)) -Wall -Wextra

# Rules

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS)  $^ -o $@

clean:

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
