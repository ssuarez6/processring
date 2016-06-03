#include "plp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <typeinfo>
#include <unistd.h>

using namespace std;


Plp::Plp(){
	terminoTareas = false;
}

int Plp::genRndmTareas(){
	srand (time(NULL));
	int n = rand() % MAX_TAREAS + 3;
	return n;
}

void Plp::initMensaje(int nTareas){
	Mensaje mensaje;
	mensaje.tareas[nTareas];
	mensaje.estadisticas[nTareas];
	for (int i = 0; i < nTareas; ++i){
		int n = rand() % 6 + 1;
		Tarea t; Estadistica e;
		t.asignado = false;
		stringstream  tmp;
		tmp << "tarea0" << n;
		memcpy(t.tareaAEjecutar, tmp.str().c_str(), sizeof(tmp.str().c_str()));
		memcpy(e.tareaAEjecutar, tmp.str().c_str(), sizeof(tmp.str().c_str()));
		t.procesoId = 0; e.procesoId = 0;
		t.hiloId = 0; e.hiloId = 0;
		mensaje.tareas[i] = t;
		mensaje.estadisticas[i] = e;
	}
	mensaje.nTareas = nTareas;
	mensaje.nEstadisticas = 0;
	this->setMensaje(&mensaje);
}


void Plp::procesarMensaje(){
	if(esHoraDeTerminar()){
		cerr << "YA ACABO!!!\n" << endl;
	}
}

int main(){
	Plp* me = new Plp();
	//int nTareas = me->genRndmTareas();
	int nTareas = 3;
	me->initMensaje(nTareas);
	me->imprimirMensaje();
	int n = 1;
	while(!me->esHoraDeTerminar()){
//		cerr << "Entre al while en plp\n";
		me->leerMensaje();
		cerr << n << " vez que el mensaje vuelve\n";
		++n;
		me->procesarMensaje();
		me->imprimirMensaje();
	}
	cerr << "Todas las tareas se han ejecutado y terminado." << endl;

	return 0;
}
