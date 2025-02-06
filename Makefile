CC = g++
CPPFLAGS = -g -Wall -std=c++17

all: data

data: data.cpp Hashtable.h
	$(CC) $(CPPFLAGS) $< -o $@

HashtableTest: data.cpp Hashtable.h
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f data