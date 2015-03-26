CXX=/home/mbailey/111/bin/c++
CC=/home/mbailey/111/bin/c++

mem:	mem.o secded.o
	$(CXX) -o mem mem.o secded.o

secded.o:	secded.cc secded.h mem.h

clean:
	rm -f secded.o mem
