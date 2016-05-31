#include "plp.h"
//#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

int Plp::genRndmTareas(){
	return -1;
}

void Plp::initMensaje(){
	Mensaje* mensaje = this->getMensaje();

	Tarea* t;
	t->asignado = true;
	char texto[64] = "una tarea a ejecutar";
	memcpy(t->tareaAEjecutar, texto, strlen(texto)+1);
	t->procesoId = 0;
	t->hiloId = -1;

	Estadistica* e;
	memcpy(e->tareaAEjecutar, texto, strlen(texto)+1);
	e->procesoId = 0;
	e->hiloId = -1;

	mensaje->nTareas = 1;
	mensaje->nEstadisticas = 1;
	mensaje->tareas[mensaje->nTareas];
	mensaje->estadisticas[mensaje->nEstadisticas];
	mensaje->tareas[0] = *t;
	mensaje->estadisticas[0] = *e;
}

void Plp::generarTareas(){

}
void Plp::procesarMensaje(){}

int main(){
	Plp* me = new Plp();
	me->initMensaje();
	me->printMessagetoErr();
	me->imprimirMensaje();
	me->leerMensaje();
	me->printMessagetoErr();
	return 0;
}
