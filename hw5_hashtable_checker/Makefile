CC = g++
CPPFLAGS = -g -Wall -std=c++17
GTEST_DIR = /opt/homebrew/Cellar/googletest/1.15.2
GTEST_LL = -I/opt/homebrew/opt/googletest/include -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread

all: HashtableTest
	./HashtableTest

HashtableTest: HashtableTest.cpp ../Hashtable.h
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $@

.PHONY: clean test

clean:
	rm -f HashtableTest


	