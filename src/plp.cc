#include "plp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <typeinfo>
#include <unistd.h>

using namespace std;

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
		memcpy(t.tareaAEjecutar, tmp.str().c_str(), 7*sizeof(char));
		memcpy(e.tareaAEjecutar, tmp.str().c_str(), 7*sizeof(char));
		t.procesoId = -1; e.procesoId = -1;
		t.hiloId = -1; e.hiloId = -1;
		mensaje.tareas[i] = t;
		mensaje.estadisticas[i] = e;
	}
	mensaje.nTareas = nTareas;
	mensaje.nEstadisticas = 0;
	this->setMensaje(&mensaje);
}


void Plp::procesarMensaje(){
	Mensaje* mensaje = this->getMensaje();
	int tareasEjecutadas = 0;
	for (int i = 0; i < mensaje->nEstadisticas; ++i){
		if(mensaje->estadisticas[i].procesoId > -1 and 
			mensaje->estadisticas[i].hiloId > -1)
			++tareasEjecutadas;
	}
	if(tareasEjecutadas == mensaje->nTareas)
		this->terminoTareas = true;
}

int main(){
	Plp* me = new Plp();
	int nTareas = me->genRndmTareas();
	me->initMensaje(nTareas);
	write(1, me->getMensaje(), sizeof(Mensaje));
	//me->printMessagetoErr(); //para debuggear
	while(!terminoTareas){
		Mensaje m;
		read(0, &m, sizeof(Mensaje));
		me->setMensaje(&m);
		me->procesarMensaje();
	}
	cerr << "Todas las tareas se han ejecutado y terminado." << endl;
	//me->printMessagetoErr();
	
	return 0;
}