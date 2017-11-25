#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include "ListaPontos.h"
#include "lista.h"

void solucao_inicial(node *lista_ponto, int facilidades);
void pontos_cobertos(node *lista_ponto, ponto *solucao);

#endif