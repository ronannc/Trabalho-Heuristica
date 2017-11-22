#pragma once
#include "Simulated_Annealing.h"
#include <time.h>
void GreedyRandomizedConstruction(ponto *solucao_parcial, node *lista_ponto, int facilidades);
void GRASP_cobrindo_ponto(node *lista_ponto, int x, int y);
void GRASP_descobrindo_ponto(node *lista_ponto, int x, int y);
int GRASP_demanda_coberta(node *lista_ponto, ponto *solucao);
int GRASP_demanda_coberta(node *lista_ponto, int x, int y);
void LocalSearch(ponto *solucao_parcial, node *lista_ponto);


void GRASP(node *lista_pontos, int facilidades, int max_iter) {

	/*solução*/
	ponto *solucao;
	solucao = (ponto *)malloc(sizeof(ponto));

	inicia_pontos(solucao);

	/*solução parcial - modificada a cada iteração do GRASP*/
	ponto *solucao_parcial;
	solucao_parcial = (ponto *)malloc(sizeof(ponto));

	inicia_pontos(solucao_parcial);

	/*inicio grasp*/
	//for (int i = 0; i < max_iter; i++) {
		/*gera a solução inicial*/
		GreedyRandomizedConstruction(solucao_parcial ,lista_pontos, facilidades);
		/*busca local na solução afim de buscar o melhor local*/
		LocalSearch(solucao_parcial, lista_pontos);

	//}
	
}

/*Gera a solução inicial aleatoria*/
void GreedyRandomizedConstruction(ponto *solucao_parcial, node *lista_ponto, int facilidades) {

	srand(time(NULL));

	int id = 0;

	for (int i = 0; i < facilidades; i++) {
		/*sorteia um id que ainda nao foi sorteado*/
		do {
			id = rand() % lista_ponto->tam;
			/*enquanto conter na lista ponto um ponto ja sorteado é sorteado outro id*/
		} while (contens_pontos(solucao_parcial, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y));
		/*insiro na lista o novo ponto*/
		insereFim_pontos(solucao_parcial, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y);
		/*manda cobrir os postos q estao no raio*/
		GRASP_cobrindo_ponto(lista_ponto, numPos(lista_ponto, id).cord_x, numPos(lista_ponto, id).cord_y);
	}
	/*solução inicial gerada com o tamanho igual ao numero de facilidades disponiveis*/

	printf("Solução inicial\n");

	exibe_pontos(solucao_parcial);

	/*vejo quais os pontos foram cobertos por essa solução inicial e a demanda coberta*/
	printf("Demanda coberta: %d\n", GRASP_demanda_coberta(lista_ponto, solucao_parcial));
}

int GRASP_demanda_coberta(node *lista_ponto, ponto *solucao) {
	
	int demanda_coberta = 0;

	/*calculando a demanda coberta*/
	for (int i = 0; i < lista_ponto->tam; i++) {

		if (numPos(lista_ponto, i).coberto) {
			demanda_coberta += numPos(lista_ponto, i).demanda;
		}
	}
	return demanda_coberta;
}

int GRASP_demanda_coberta(node *lista_ponto, int x, int y) {

	/*calculando a demanda coberta*/
	return numPos(lista_ponto, procura(lista_ponto, x, y)).demanda;
}

void GRASP_cobrindo_ponto(node *lista_ponto, int x, int y) {

	int id = 0;
	int idx = 0;

	/*procura na lista de pontos o ponto que tem a facilidade, esse ponto eh da solução*/
	id = procura(lista_ponto, x, y);

	/*iterajo em todos os pontos que estao dentro do raio*/
	for (int j = 0; j < numPos(lista_ponto, id).raio->tam; j++) {
		/*procuro o ponto coberto na lista de pontos*/
		idx = procura(lista_ponto, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_x, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_y);
		/*incremento falando que ele foi coberto -  isso me da a quantidade de vezes que ele foi coberto*/
		incrementa_coberto(lista_ponto, idx);
	}	
}

void GRASP_descobrindo_ponto(node *lista_ponto, int x, int y) {

	int id = 0;
	int idx = 0;

	/*procura na lista de pontos o ponto que tem a facilidade, esse ponto eh da solução*/
	id = procura(lista_ponto, x, y);

	/*iterajo em todos os pontos que estao dentro do raio*/
	for (int j = 0; j < numPos(lista_ponto, id).raio->tam; j++) {
		/*procuro o ponto coberto na lista de pontos*/
		idx = procura(lista_ponto, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_x, (numPos_pontos((numPos(lista_ponto, id).raio), j)).cord_y);
		/*incremento falando que ele foi coberto -  isso me da a quantidade de vezes que ele foi coberto*/
		decrementa_coberto(lista_ponto, idx);
	}
}

void LocalSearch(ponto *solucao_parcial, node *lista_ponto) {

	srand(time(NULL));

	int aux_id = 0;

	int max_demanda = GRASP_demanda_coberta(lista_ponto, solucao_parcial);

	/*sorteio um ponto da sulução inicial*/
	int id = rand() % solucao_parcial->tam;

	/*descrobre os pontos que ele cobre*/
	GRASP_descobrindo_ponto(lista_ponto, numPos_pontos(solucao_parcial, id).cord_x, numPos_pontos(solucao_parcial, id).cord_y);

	/*retiro esse ponto da solução e decremento os pontos que ela cobria*/
	retira_pontos(solucao_parcial, id);
	
	int demanda = GRASP_demanda_coberta(lista_ponto, solucao_parcial);

	/*procurar o melhor ponto a se colocar a facilidade com a solução parcial*/
	for (int i = 0; i < lista_ponto->tam; i++) {

		if (max_demanda < demanda + GRASP_demanda_coberta(lista_ponto, numPos(lista_ponto, i).cord_x, numPos(lista_ponto, i).cord_y)) {
			aux_id = i;
		}
	}

	insereFim_pontos(solucao_parcial, numPos(lista_ponto, aux_id).cord_x, numPos(lista_ponto, aux_id).cord_y);
	GRASP_cobrindo_ponto(lista_ponto, numPos(lista_ponto, aux_id).cord_x, numPos(lista_ponto, aux_id).cord_y);

	printf("Solução depois da busca local\n");

	exibe_pontos(solucao_parcial);

	/*vejo quais os pontos foram cobertos por essa solução inicial e a demanda coberta*/
	printf("Demanda coberta: %d\n", GRASP_demanda_coberta(lista_ponto, solucao_parcial));
}