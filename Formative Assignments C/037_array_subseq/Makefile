CFLAGS= -pedantic -Wall
test: maxSeq.o test-subseq.o
	gcc -o test maxSeq.o test-subseq.o
%.o: %.c
	gcc $(CFLAGS) -c $< 
