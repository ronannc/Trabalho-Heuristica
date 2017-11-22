
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "calc_distancia.h"
#include <stdio.h>
#include "Simulated_Annealing.h"

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
	printf("iniciada listas de lista\n");
	//system("pause");

	inicia_pontos(pontos_alcance);
	printf("iniciada listas pontos\n");
	//system("pause");

	FILE *arq_pontos;
	FILE *arq_demanda;
	
	int x, y, demanda = 0;
	int quantidade_pontos = 0;
	int raio = 0;
	int facilidades = 0;
	
	arq_pontos = fopen("Dataset/SJC324.dat", "r");
	arq_demanda = fopen("Dataset/demand-SJC324.dat", "r");

	if ((arq_pontos == NULL) ||(arq_demanda == NULL)) {

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

	//exibe(lista);

	printf("lista de pontos preenchida\n");
	//system("pause");

	for (int i = 0; i < quantidade_pontos; i++) {
		for (int j = 0; j < quantidade_pontos; j++) {
			
			if (calcula_distancia( numPos(lista, i).cord_x, numPos(lista, i).cord_y, numPos(lista, j).cord_x, numPos(lista, j).cord_y, raio)) {
				
				//printf("dentro do raio");
				//system("pause");
			
				insereFim_pontos(numPos(lista, i).raio, numPos(lista, j).cord_x, numPos(lista, j).cord_y);
			}
		}
	}
	

	exibe(lista);

	/*SA*/
	simulated_annealing(lista, facilidades);

	/*GRASP*/

	fclose(arq_demanda);
	fclose(arq_pontos);

	free(lista);
	free(pontos_alcance);

	system("pause");
}
