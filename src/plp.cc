#include "plp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;


int Plp::genRndmTareas(){
	srand (time(NULL));
	int n = rand() % 255 + 3;
	return n;
}

void Plp::initMensaje(int nTareas, Tarea* tareas){
	Estadistica estadisticas[nTareas];
	Mensaje mensaje;
	mensaje.nTareas = nTareas;
	mensaje.nEstadisticas = -1;
	std::memcpy(mensaje.tareas,tareas,nTareas);
	std::memcpy(mensaje.estadisticas,estadisticas,nTareas);
	this->setMensaje(&mensaje);
}

Tarea* Plp::generarTareas(int nTareas){
	Tarea tareas [nTareas];
	for (int i = 0; i < nTareas; ++i){
		int n = rand() % 6 + 1;
		Tarea t;
		t.asignado = false;
		ostringstream  tmp;
		tmp << "tarea0" << n;
		std::memcpy(t.tareaAEjecutar,tmp.str().c_str(),MAX_TEXT_AREA);
		t.procesoId = -1;
		t.hiloId = -1;
		tareas[i] = t;
	}
	return tareas; //this generates a warning(?)
}
void Plp::procesarMensaje(){
	Mensaje* mensaje = this->getMensaje();
	for (int i = 0; i < mensaje->nTareas; ++i){
		if(!mensaje->tareas[i].asignado){ // Condición de fin, esto o id's de procesos?
			break;
		}
	}
	this->terminoTareas = true;
}

int main(){
	Plp* me = new Plp();
	int nTareas = me->genRndmTareas();
	Tarea* tareas = me->generarTareas(nTareas);
	me->initMensaje(nTareas,tareas);
	me->printMessagetoErr();
	me->procesarMensaje();
}

