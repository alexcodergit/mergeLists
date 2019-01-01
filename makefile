
CC=g++

file = MergeSortedLists.cpp

OBJ = MergeSortedLists.o

/%.o: %.cpp $(file)
	$(CC) -c -o $@

MergeSortedLists: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f *.o *.exe