#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Simulated_Annealing.h"
#include "GRASP.h"

const int max_iter = 300;

int main()
{
    node *lista;
    lista = (node *)malloc(sizeof(node));

    ponto *pontos_alcance;
    pontos_alcance = (ponto *)malloc(sizeof(ponto));

    if (!lista) {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }

    if (!pontos_alcance) {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }

    inicia(lista);
    //printf("iniciada listas de lista\n");
    //system("pause");

    inicia_pontos(pontos_alcance);
    //printf("iniciada listas pontos\n");
    //system("pause");

    FILE *arq_pontos;
    FILE *arq_demanda;

    int x, y, demanda = 0;
    int quantidade_pontos = 0;
    int raio = 0;
    int facilidades = 0;

    arq_pontos = fopen("Dataset/SJC324.dat", "r");
    arq_demanda = fopen("Dataset/demand-SJC324.dat", "r");

    if ((arq_pontos == NULL) || (arq_demanda == NULL)) {

        printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else {

        fscanf(arq_pontos, "%d %d %d\n", &quantidade_pontos, &facilidades, &raio);

        printf("quant. pontos: %d, quant. facilidades: %d, raio: %d\n", quantidade_pontos, facilidades, raio);

        for (int i = 0; i < quantidade_pontos; i++) {
            fscanf(arq_demanda, "%d\n", &demanda);
            fscanf(arq_pontos, "%d %d\n", &x, &y);
            insereFim(lista, x, y, demanda);
        }
    }

    fclose(arq_demanda);
    fclose(arq_pontos);

    //exibe(lista);

    printf("lista de pontos preenchida\n");
    //system("pause");

    for (int i = 0; i < quantidade_pontos; i++) {
        for (int j = 0; j < quantidade_pontos; j++) {

            if (calcula_distancia(numPos(lista, i).cord_x, numPos(lista, i).cord_y, numPos(lista, j).cord_x, numPos(lista, j).cord_y, raio)) {

                //printf("dentro do raio");
                //system("pause");

                insereFim_pontos(numPos(lista, i).raio, numPos(lista, j).cord_x, numPos(lista, j).cord_y, numPos(lista, j).demanda);
            }
        }
    }


    //exibe(lista);

    /*inicializando o tempo*/
    clock_t Ticks[2];

    FILE *pf;

    /* Abre arquivo txt para escrita */
    if ((pf = fopen("Saida_trabalhoHeuristica.txt", "a")) == NULL)
    {
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    

    /*SA*/
    //simulated_annealing(lista, facilidades);

    fprintf(pf, "GRASP max_iter: %d\n", max_iter);

    /*GRASP*/
    for (int j = 1; j < 6; j++) {
        fprintf(pf, "pontos: %d facilidades: %d raio: %d\n", quantidade_pontos, j, raio);
        Ticks[0] = clock();
            GRASP(lista, j, max_iter, pf);
        Ticks[1] = clock();
        printf("Tempo gasto: %d\n\n", (Ticks[1] - Ticks[0]) / CLOCKS_PER_SEC);

        fprintf(pf, "Tempo gasto: %d\n\n", (Ticks[1] - Ticks[0]) / CLOCKS_PER_SEC);
    }
    

    free(lista);
    free(pontos_alcance);
    fclose(pf);
    system("pause");
}