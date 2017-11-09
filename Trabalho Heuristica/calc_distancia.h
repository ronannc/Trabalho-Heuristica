#include "math.h"
int calcula_distancia(int x1, int y1, int x2, int y2, int raio) {
	
	if (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) <= raio) {
		return 1;
	}
	else {
		return 0;
	}
}