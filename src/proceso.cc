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
	}
}
