FLAGS = -c -Wall -Werror -Wextra

.PHONY: clean

peter-quest : main.o board.o box.o hero.o
	gcc -o $@ $^

main.o: main.c main.h
	gcc $(FLAGS) $< 

board.o: board.c board.h main.h box.h
	gcc $(FLAGS) $<

box.o: box.c box.h main.h hero.h
	gcc $(FLAGS) $<

hero.o: hero.c hero.h
	gcc $(FLAGS) $<

clean:
	rm -f *.o