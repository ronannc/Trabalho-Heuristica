#include <stdio.h>
#include <stdlib.h>

struct Pontos {
	int cord_x;
	int cord_y;
	int demanda;
	struct Pontos *prox;
	int tam;
};
typedef struct Pontos ponto;

void inicia_pontos(ponto *LISTA)
{
	LISTA->prox = NULL;
	LISTA->tam = 0;
}

int vazia_pontos(ponto *LISTA)
{
	if (LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

ponto *aloca_pontos(int x, int y, int demanda)
{
	ponto *novo = (ponto *)malloc(sizeof(ponto));
	if (!novo) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else {
		//printf("Novo elemento: "); scanf("%d", &novo->num);
		novo->cord_x = x;
		novo->cord_y = y;
		novo->demanda = demanda;
		return novo;
	}
}

void insereFim_pontos(ponto *LISTA, int x, int y, int demanda)
{
	ponto *novo = aloca_pontos(x, y, demanda);
	novo->prox = NULL;

	if (vazia_pontos(LISTA))
		LISTA->prox = novo;
	else {
		ponto *tmp = LISTA->prox;

		while (tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	LISTA->tam++;
}

void insereInicio_pontos(ponto *LISTA, int x, int y, int demanda)
{
	ponto *novo = aloca_pontos(x, y, demanda);
	ponto *oldHead = LISTA->prox;

	LISTA->prox = novo;
	novo->prox = oldHead;

	LISTA->tam++;
}

Pontos numPos_pontos(ponto *LISTA, int id) {

	ponto *tmp;

	if (vazia_pontos(LISTA)) {
		printf("Lista vazia!\n\n");
		return *tmp;
	}


	tmp = LISTA->prox;

	for (int i = 0; i < id; i++) {
		tmp = tmp->prox;
	}
	return *tmp;
}

void exibe_pontos(ponto *LISTA)
{
	if (vazia_pontos(LISTA)) {
		printf("Lista vazia!\n\n");
		return;
	}

	ponto *tmp;
	tmp = LISTA->prox;
	while (tmp != NULL) {
		printf("x: %d, y: %d\n", tmp->cord_x, tmp->cord_y);
		tmp = tmp->prox;
	}
}

void libera_pontos(ponto *LISTA)
{
	if (!vazia_pontos(LISTA)) {
		ponto *proxNode,
			*atual;

		atual = LISTA->prox;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void insere_pontos(ponto *LISTA, int x, int y, int id, int demanda)
{
	int count;

	if (id >= 0 && id < LISTA->tam) {
		if (id == 0)
			insereInicio_pontos(LISTA, x, y, demanda);
		else {
			ponto *atual = LISTA->prox,
				*anterior = LISTA;
			ponto *novo = aloca_pontos(x, y, demanda);

			for (count = 0; count < id; count++) {
				anterior = atual;
				atual = atual->prox;
			}
			anterior->prox = novo;
			novo->prox = atual;
			LISTA->tam++;
		}

	}
	else
		printf("Elemento invalido\n\n");
}

ponto *retiraInicio_pontos(ponto *LISTA)
{
	if (LISTA->prox == NULL) {
		printf("Lista ja esta vazia\n");
		return NULL;
	}
	else {
		ponto *tmp = LISTA->prox;
		LISTA->prox = tmp->prox;
		LISTA->tam--;
		return tmp;
	}

}

ponto *retiraFim_pontos(ponto *LISTA)
{
	if (LISTA->prox == NULL) {
		printf("Lista ja vazia\n\n");
		return NULL;
	}
	else {
		ponto *ultimo = LISTA->prox,
			*penultimo = LISTA;

		while (ultimo->prox != NULL) {
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}

		penultimo->prox = NULL;
		LISTA->tam--;
		return ultimo;
	}
}

ponto *retira_pontos(ponto *LISTA, int id)
{
	int count;

	if (id >= 0 && id < LISTA->tam) {
		if (id == 0)
			return retiraInicio_pontos(LISTA);
		else {
			ponto *atual = LISTA->prox,
				*anterior = LISTA;

			for (count = 0; count < id; count++) {
				anterior = atual;
				atual = atual->prox;
			}

			anterior->prox = atual->prox;
			LISTA->tam--;
			return atual;
		}

	}
	else {
		printf("Elemento invalido\n\n");
		return NULL;
	}
}

int contens_pontos(ponto *LISTA, int x, int y) {

	for (int i = 0; i < LISTA->tam; i++) {

		if ((numPos_pontos(LISTA, i).cord_x == x) && (numPos_pontos(LISTA, i).cord_y == y)) {
			return 1;
		}
	}
	return 0;
}