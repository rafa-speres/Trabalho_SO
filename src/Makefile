all: compile

compile:
	@gcc -o main.run *.c ./threads/*.c -pthread -Wall -I .

compile-debug:
	@gcc -o main.run *.c ./threads/*.c -pthread -DDEBUG -Wall -I .

run:
	@./main.run

clear:
	@rm ./traces/*.trace

test:
	@make all --no-print-directory && make run --no-print-directory < ./testes/1.in  

test-debug:
	@make compile-debug --no-print-directory  && make run --no-print-directory < ./testes/1.in  

zip:
	@zip -r runCodes.zip *.c *.h Makefile
