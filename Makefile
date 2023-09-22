SRCS := main.cpp Logger.cpp

all: $(SRCS) Logger.h
	clang $(SRCS) -std=c++98 -Wall -Wextra -lstdc++

run: all
	./a.out

clean:
	rm ./a.out -f
