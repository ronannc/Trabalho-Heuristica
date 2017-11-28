all:
	gcc -o lista.o -c lista.c
	gcc -o ListaPontos.o -c ListaPontos.c
	gcc -o Simulated_Annealing.o -c Simulated_Annealing.c
	gcc -o GRASP.o -c GRASP.c
	gcc -o  main lista.o ListaPontos.o Simulated_Annealing.o GRASP.o kernel.c -lm

run:
	./main