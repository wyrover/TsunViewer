BIN=Build/StupidViewer

CXX=clang++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -IExternals/include
	
LDLIBS=-LExternals/lib -lcurl -lrestclient-cpp -lSDL2 -lSDL2_image
	
SRCS=$(shell find Source/ -type f -name '*.cpp')
	
OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)
	g++ $(OBJS) -o $(BIN) $(LDLIBS)

clean:
	rm -f $(OBJS)

.PHONY: all clean
