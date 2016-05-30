#include "proceso.h"

void Proceso::setMensaje(Mensaje* m){
	this->mensaje = m;
}

Mensaje* Proceso::getMensaje(){
	return this->mensaje;
}

void Proceso::imprimirMensaje(){
	setMensaje(getMensaje());
}

Mensaje* Proceso::leerMensaje(){
	return 0;
}
