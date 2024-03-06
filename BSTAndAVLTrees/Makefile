compiler = g++
flags = -g -Wall -std=c++11
compile = $(compiler) $(flags)

scheduling: scheduling.cpp bst.h print_bst.h avlbst.h
	$(compile) scheduling.cpp bst.h print_bst.h avlbst.h -o scheduling

.PHONY: clean
clean:
	rm -f scheduling

