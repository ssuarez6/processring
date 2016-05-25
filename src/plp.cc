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
		cerr << "El PLP va a mandar un numero al siguiente." << endl;
		cout << 4 << endl;
		cerr << "Recibiendo el id del ultimo pcp" << endl;
		int n=-1;
		cin >> n;
		cerr << "Numero recibido (-1 si error) " << n << endl;
}
