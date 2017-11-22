#pragma once
#include "lista.h"
#include <time.h>
void solucao_inicial(node *lista_ponto, int facilidades);
void pontos_cobertos(node *lista_ponto, ponto *solucao);



void simulated_annealing(node *lista_pontos, int facilidades) {
	
	solucao_inicial(lista_pontos, facilidades);

}


/*Gera a solução inicial aleatoria*/
void solucao_inicial(node *lista_ponto, int facilidades) {

	ponto *solucao;
	solucao = (ponto *)malloc(sizeof(ponto));

	inicia_pontos(solucao);

	srand(time(NULL));
	int id = 0;
	for (int i = 0; i < facilidades; i++) {
		do {
			id = rand() % lista_ponto->tam;
		} while (contens_pontos(solucao, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y));
		
		
		insereFim_pontos(solucao, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y);
	}

	printf("Solução inicial\n");

	exibe_pontos(solucao);

	pontos_cobertos(lista_ponto, solucao);

	
}

void pontos_cobertos(node *lista_ponto, ponto *solucao) {
	
	int id = 0;
	int idx = 0;
	for (int i = 0; i < solucao->tam; i++) {

		id = procura(lista_ponto, numPos_pontos(solucao, i).cord_x, numPos_pontos(solucao, i).cord_y);

		for (int j = 0; j < numPos(lista_ponto, id).raio->tam; j++) {
			
		idx = procura(lista_ponto, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_x, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_y);
		incrementa_coberto(lista_ponto, idx);
		}
	}

	printf("pontos cobertos\n");
	for (int i = 0; i < lista_ponto->tam; i++) {

		if (numPos(lista_ponto, i).coberto) {
			printf("x: %d y: %d  coberto: %d\n", numPos(lista_ponto, i).cord_x, numPos(lista_ponto, i).cord_y, numPos(lista_ponto, i).coberto);
		}		
	}
}