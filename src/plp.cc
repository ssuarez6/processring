#include "plp.h"
#include <time.h>
#include <stdlib.h>

int Plp::genRndTareas(){
	int tareas;
	srand(time(NULL));
	tareas = rand() % 255 + 3;
	return tareas;
}

void Plp::initMensaje(){
	
}
