#include "proceso.h"
#include <unistd.h>
#include <iostream>

using namespace std;
void Proceso::setMensaje(Mensaje* m){
	this->mensaje = m;
}

Mensaje* Proceso::getMensaje(){
	return this->mensaje;
}

void Proceso::printMessagetoErr(){
	for (int i=0; i<(*mensaje).nTareas; ++i){
		cerr << "Tarea #" << i << ". A Ejecutar: "
			<< (*mensaje).tareas[i].tareaAEjecutar << endl;
		cerr << "Estadistica #" << i << " HiloID" << (*mensaje).estadisticas[i].hiloId << endl;
		cerr << "ProcesoID: " << (*mensaje).estadisticas[i].procesoId << endl;
	}
}

bool Proceso::esHoraDeTerminar(){
	//printMessagetoErr();
	for(int i=0; i<mensaje->nTareas; ++i){
		if(mensaje->estadisticas[i].procesoId == 0)
			return false;
	}
	cerr << "Ya es hora de terminar\n";
	return true;
}

void Proceso::imprimirMensaje(){
	Mensaje* m = this->getMensaje();
	int tareas = m->nTareas;
	int estadisticas = m->nEstadisticas;
	write(1, &tareas, sizeof(tareas));
	write(1, &estadisticas, sizeof(estadisticas));
	for (int i=0; i<m->nTareas; ++i){
		write(1, &(m->tareas[i]), sizeof(Tarea));
		write(1, &(m->estadisticas[i]), sizeof(Estadistica));
	}
}

void Proceso::leerMensaje(){
	Mensaje msg;
	int tareas, estadisticas;
	read(0, &tareas, sizeof(tareas));
	read(0, &estadisticas, sizeof(estadisticas));
	msg.nTareas = tareas;
	msg.nEstadisticas = estadisticas;
	for(int i=0; i<tareas; ++i){
		Tarea t; Estadistica e;
		read(0, &t, sizeof(Tarea));
		read(0, &e, sizeof(Estadistica));
		msg.tareas[i] = t;
		msg.estadisticas[i] = e;
	}
	this->setMensaje(&msg);
}
