compiler = g++
flags = -g -Wall -std=c++11
compile = $(compiler) $(flags)

rsa: main.cpp Hashtable.h
	$(compile) main.cpp Hashtable.h -o hashTable

.PHONY: clean
clean:
	rm -f rsa
