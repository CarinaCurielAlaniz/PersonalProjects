compiler = g++
flags = -g -Wall -std=c++11
compile = $(compiler) $(flags)

rsa: main.cpp encry.cpp decry.cpp commands.cpp
	$(compile) main.cpp encry.cpp decry.cpp commands.cpp -o rsa

.PHONY: clean
clean:
	rm -f rsa
