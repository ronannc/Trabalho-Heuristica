#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"

void inicia(node *LISTA)
{
    LISTA->raio = (ponto *)malloc(sizeof(ponto));
    inicia_pontos(LISTA->raio);

    LISTA->prox = NULL;
    LISTA->tam = 0;

}

int vazia(node *LISTA)
{
    if (LISTA->prox == NULL)
        return 1;
    else
        return 0;
}

node *aloca(int x, int y, int demanda)
{
    node *novo = (node *)malloc(sizeof(node));
    if (!novo) {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else {
        //printf("Novo elemento: "); scanf("%d", &novo->num);
        novo->coberto = 0;
        novo->cord_x = x;
        novo->cord_y = y;
        novo->demanda = demanda;
        novo->raio = (ponto *)malloc(sizeof(ponto));
        inicia_pontos(novo->raio);
        return novo;
    }
}

void insereFim(node *LISTA, int x, int y, int demanda)
{
    node *novo = aloca(x, y, demanda);
    novo->prox = NULL;

    if (vazia(LISTA))
        LISTA->prox = novo;
    else {
        node *tmp = LISTA->prox;

        while (tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    LISTA->tam++;
}

void insereInicio(node *LISTA, int x, int y, int demanda)
{
    node *novo = aloca(x, y, demanda);
    node *oldHead = LISTA->prox;

    LISTA->prox = novo;
    novo->prox = oldHead;

    LISTA->tam++;
}

Node numPos(node *LISTA, int id) {
    node *tmp;

    if (vazia(LISTA)) {
        printf("Lista vazia!\n\n");
        return *tmp;
    }

    
    tmp = LISTA->prox;

    for (int i = 0; i < id; i++) {
        tmp = tmp->prox;
    }
    return *tmp;
}

void exibe(node *LISTA)
{
    if (vazia(LISTA)) {
        printf("Lista vazia!\n\n");
        return;
    }

    node *tmp;
    tmp = LISTA->prox;

    while (tmp != NULL) {
        printf("x: %d, y: %d, demanda: %d coberto: %d\n", tmp->cord_x, tmp->cord_y, tmp->demanda, tmp->coberto);
        printf("Pntos no alcance\n");
        exibe_pontos(tmp->raio);
        tmp = tmp->prox;
    }
}

void libera(node *LISTA)
{
    if (!vazia(LISTA)) {
        node *proxNode,
            *atual;

        atual = LISTA->prox;
        while (atual != NULL) {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

void insere(node *LISTA, int x, int y, int demanda, int id)
{
    int count;

    if (id >= 0 && id < LISTA->tam) {
        if (id == 0)
            insereInicio(LISTA, x, y, demanda);
        else {
            node *atual = LISTA->prox,
                *anterior = LISTA;
            node *novo = aloca(x, y, demanda);

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

node *retiraInicio(node *LISTA)
{
    if (LISTA->prox == NULL) {
        printf("Lista ja esta vazia\n");
        return NULL;
    }
    else {
        node *tmp = LISTA->prox;
        LISTA->prox = tmp->prox;
        LISTA->tam--;
        return tmp;
    }

}

node *retiraFim(node *LISTA)
{
    if (LISTA->prox == NULL) {
        printf("Lista ja vazia\n\n");
        return NULL;
    }
    else {
        node *ultimo = LISTA->prox,
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

node *retira(node *LISTA, int id)
{
    int count;

    if (id >= 0 && id < LISTA->tam) {
        if (id == 0)
            return retiraInicio(LISTA);
        else {
            node *atual = LISTA->prox,
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

int contens(node *LISTA, int x, int y) {

    for (int i = 0; i < LISTA->tam; i++) {

        if ((numPos(LISTA, i).cord_x == x) && (numPos(LISTA, i).cord_y == y)) {
            return 1;
        }
    }
    return 0;
}

int procura(node *LISTA, int x, int y) {

    for (int i = 0; i < LISTA->tam; i++) {

        if ((numPos(LISTA, i).cord_x == x) && (numPos(LISTA, i).cord_y == y)) {
            return i;
        }
    }
    return -1;
}

void incrementa_coberto(node *LISTA, int id) {
        
        node *tmp;

        if (vazia(LISTA)) {
            printf("Lista vazia!\n\n");
        }

        tmp = LISTA->prox;

        for (int i = 0; i < id; i++) {
            tmp = tmp->prox;
        }   
        tmp->coberto++;
}

void decrementa_coberto(node *LISTA, int id) {

    node *tmp;

    if (vazia(LISTA)) {
        printf("Lista vazia!\n\n");
    }

    tmp = LISTA->prox;

    for (int i = 0; i < id; i++) {
        tmp = tmp->prox;
    }
    tmp->coberto--;
}

void zera_pontos_cobertos(node *LISTA) {
    node *tmp;

    if (vazia(LISTA)) {
        printf("Lista vazia!\n\n");
    }

    tmp = LISTA->prox;

    for (int i = 0; i < LISTA->tam; i++) {
        
        tmp->coberto = 0;
        tmp = tmp->prox;
    }   
}

int calcula_distancia(int x1, int y1, int x2, int y2, int raio) {
    
    if (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) <= raio) {
        return 1;
    }
    else {
        return 0;
    }
}