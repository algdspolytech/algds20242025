test: ull.o testUll.o unity.o
	gcc -Wall -Werror -Wextra -o test testUnrolledLinkedList.o UnrolledLinkedList.o unity.o
ull.o: UnrolledLinkedList.c UnrolledLinkedList.h
	gcc -Wall -Werror -Wextra -c UnrolledLinkedList.c
testUll.o: testUnrolledLinkedList.c UnrolledLinkedList.h
	gcc -Wall -Werror -Wextra -c testUnrolledLinkedList.c
unity.o: unity.h unity.c
	gcc -Wall -Werror -Wextra -c unity.c
clean:
	rm -rf *.o *.exe test

