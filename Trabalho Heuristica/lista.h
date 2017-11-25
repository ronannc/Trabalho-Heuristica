#ifndef LISTA_H
#define LISTA_H

#include "ListaPontos.h"

// Estrutura:
struct Node {
	int cord_x;
	int cord_y;
	int demanda;
	ponto *raio;
	struct Node *prox;
	int tam;
	int coberto;
};
typedef struct Node Node;
typedef Node node;

// Sub-rotinas:
void inicia(node *LISTA);
int vazia(node *LISTA);
node *aloca(int x, int y, int demanda);
void insereFim(node *LISTA, int x, int y, int demanda);
void insereInicio(node *LISTA, int x, int y, int demanda);
Node numPos(node *LISTA, int id);
void exibe(node *LISTA);
void libera(node *LISTA);
void insere(node *LISTA, int x, int y, int demanda, int id);
node *retiraInicio(node *LISTA);
node *retiraFim(node *LISTA);
node *retira(node *LISTA, int id);
int contens(node *LISTA, int x, int y);
int procura(node *LISTA, int x, int y);
void incrementa_coberto(node *LISTA, int id);
void decrementa_coberto(node *LISTA, int id);
void zera_pontos_cobertos(node *LISTA);
int calcula_distancia(int x1, int y1, int x2, int y2, int raio);


#endif