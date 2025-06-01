CXX = g++
CXXFLAGS = -Wall -g -W -pedantic -std=c++23
TARGET = main
OBJS = main.o token.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) -c main.cpp

token.o: token.cpp token.h
	$(CXX) $(CXXFLAGS) -c token.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
