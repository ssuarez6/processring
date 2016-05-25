#include "plp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int Plp::genRndTareas(){
	int tareas;
	srand(time(NULL));
	tareas = rand() % 255 + 3;
	return tareas;
}

void Plp::initMensaje(){

}

int main(){
		cerr << "PLP creado\n";
}
