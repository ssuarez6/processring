#include "plp.h"
//#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int Plp::genRndmTareas(){
	return -1;
}

void Plp::initMensaje(){

}

void Plp::generarTareas(){

}
void Plp::procesarMensaje(){}

int main(){
	Plp* me = new Plp();
	cerr << "PLP creado\n";
	cerr << "El PLP va a mandar un numero al siguiente." << endl;
	cout << 4 << endl;
	cerr << "Recibiendo el id del ultimo pcp" << endl;
	int n=-1;
	cin >> n;
	cerr << "Numero recibido (-1 si error) " << n << endl;
}
