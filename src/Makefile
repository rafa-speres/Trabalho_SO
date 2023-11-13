all: compile

compile:
	@gcc -o main.run *.c -pthread -Wall -I .

run:
	@./main.run

test:
	@make all --no-print-directory && make run --no-print-directory < ./testes/1.in  

zip:
	@zip -r runCodes.zip *.c *.h Makefile
