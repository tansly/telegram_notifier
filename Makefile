CXX=g++
CXXFLAGS=-std=c++17 $(shell curl-config --cflags) -pthread -Wall
LDFLAGS=$(shell curl-config --libs) -pthread -lboost_system
STRIP=strip

.PHONY: all
all: debug

.PHONY: debug
debug: CXXFLAGS+=-ggdb -Og
debug: telegrambotd

.PHONY: release
release: CXXFLAGS+=-O2
release: telegrambotd
	$(STRIP) telegrambotd

bot.o: bot.h config.h curl_handle.h global.h bot.cpp

curl_handle.o: curl_handle.h curl_handle.cpp

main.o: bot.h config.h curl_handle.h global.h queue.h main.cpp

global.o: global.h global.cpp

telegrambotd: config.h bot.h bot.o curl_handle.h curl_handle.o main.o queue.h global.h global.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) curl_handle.o main.o bot.o global.o -o telegrambotd

.PHONY: clean
clean:
	rm -f *.o telegrambotd
