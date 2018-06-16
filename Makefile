CXX=g++
CXXFLAGS=-std=c++17 -O0 -ggdb $(shell curl-config --cflags)
LDFLAGS=$(shell curl-config --libs)

main: config.h bot.h bot.cpp curl_handle.h curl_handle.cpp main.cpp queue.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) curl_handle.cpp main.cpp bot.cpp -o main
