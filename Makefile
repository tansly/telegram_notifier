CXX=g++
CXXFLAGS=-std=c++17 -O2 $(shell curl-config --cflags) -pthread -Wall
LDFLAGS=$(shell curl-config --libs) -pthread -lboost_system

main: config.h bot.h bot.cpp curl_handle.h curl_handle.cpp main.cpp queue.h global.h global.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) curl_handle.cpp main.cpp bot.cpp global.cpp -o main
