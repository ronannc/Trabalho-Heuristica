#ifndef GRASP_H
#define GRASP_H

#include "ListaPontos.h"
#include "lista.h"

void GRASP(node *lista_pontos, int facilidades, int max_iter, FILE *arq);
void GreedyRandomizedConstruction(ponto *solucao_parcial, node *lista_ponto, int facilidades);
void GRASP_cobrindo_ponto(node *lista_ponto, int x, int y);
void GRASP_descobrindo_ponto(node *lista_ponto, int x, int y);
int GRASP_demanda_coberta(node *lista_ponto);
int GRASP_demanda_coberta_xy(node *lista_ponto, int x, int y);
void LocalSearch(ponto *solucao_parcial, node *lista_ponto);
void Update_Soluction(ponto *solucao_parcial, node *lista_pontos, ponto *solucao);

#endif