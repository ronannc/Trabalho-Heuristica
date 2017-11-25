#ifndef LISTA_PONTOS_H
#define LISTA_PONTOS_H

// Estrutura:
struct Pontos {
	int cord_x;
	int cord_y;
	int demanda;
	struct Pontos *prox;
	int tam;
};
typedef struct Pontos Pontos;
typedef Pontos ponto;

// Sub-rotinas:
void inicia_pontos(ponto *LISTA);
int vazia_pontos(ponto *LISTA);
ponto *aloca_pontos(int x, int y, int demanda);
void insereFim_pontos(ponto *LISTA, int x, int y, int demanda);
void insereInicio_pontos(ponto *LISTA, int x, int y, int demanda);
Pontos numPos_pontos(ponto *LISTA, int id);
void exibe_pontos(ponto *LISTA);
void libera_pontos(ponto *LISTA);
void insere_pontos(ponto *LISTA, int x, int y, int id, int demanda);
void insere_pontos(ponto *LISTA, int x, int y, int id, int demanda);
ponto *retiraFim_pontos(ponto *LISTA);
ponto *retira_pontos(ponto *LISTA, int id);
int contens_pontos(ponto *LISTA, int x, int y);


#endif