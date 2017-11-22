#pragma once
#include "lista.h"
#include <time.h>
void solucao_inicial(node *lista_ponto, int facilidades);
void pontos_cobertos(node *lista_ponto, ponto *solucao);



void simulated_annealing(node *lista_pontos, int facilidades) {
	
	/*gera a solução inicial*/
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
		/*sortei um id que ainda nao foi sorteado*/
		do {
			
			id = rand() % lista_ponto->tam;
			/*enquanto conter na lista ponto um ponto ja sorteado é sorteado outro id*/
		} while (contens_pontos(solucao, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y));		
		/*insiro na lista o novo ponto*/
		insereFim_pontos(solucao, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y);
	}
	/*solução inicial gerada com o tamanho igual ao numero de facilidades disponiveis*/

	printf("Solução inicial\n");

	exibe_pontos(solucao);

	/*vejo quais os pontos foram cobertos por essa solução inicial e a demanda coberta*/
	pontos_cobertos(lista_ponto, solucao);	
}

void pontos_cobertos(node *lista_ponto, ponto *solucao) {
	
	int id = 0;
	int idx = 0;
	int demanda_coberta = 0;

	for (int i = 0; i < solucao->tam; i++) {

		/*procura na lista de pontos o ponto que tem a facilidade, esse ponto eh da solução*/
		id = procura(lista_ponto, numPos_pontos(solucao, i).cord_x, numPos_pontos(solucao, i).cord_y);

		/*iterajo em todos os pontos que estao dentro do raio*/
		for (int j = 0; j < numPos(lista_ponto, id).raio->tam; j++) {
			/*procuro o ponto coberto na lista de pontos*/
			idx = procura(lista_ponto, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_x, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_y);
			/*incremento falando que ele foi coberto -  isso me da a quantidade de vezes que ele foi coberto*/
			incrementa_coberto(lista_ponto, idx);
		}
	}

	/*printando os pontos cobertos e calculando a demanda coberta*/
	printf("pontos cobertos\n");
	for (int i = 0; i < lista_ponto->tam; i++) {

		if (numPos(lista_ponto, i).coberto) {
			demanda_coberta += numPos(lista_ponto, i).demanda;
			printf("x: %d y: %d  coberto: %d\n", numPos(lista_ponto, i).cord_x, numPos(lista_ponto, i).cord_y, numPos(lista_ponto, i).coberto);
		}		
	}
	printf("Demanda Coberta: %d\n", demanda_coberta);
}