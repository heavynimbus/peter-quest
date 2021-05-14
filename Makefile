FLAGS = -c -Wall -Werror -Wextra

.PHONY: clean

peter-quest : main.o
	gcc -o $@ $^

main.o: main.c
	gcc $(FLAGS) $< 
	
clean:
	rm -f *.o

real-clean:
	@make clean
	rm 