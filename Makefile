all: eodr.c
	gcc -o eodr eodr.c
cleanall: clean cleantxt
clean:
	rm -f eodr outputeo.txt outputdr.txt
cleantxt:
	rm -f *.txt
sanitize:
	gcc -fsanitize=address eodr.c

