#include <iostream> //entrada y salida
#include <unistd.h>
#include "pcp.h"
#include <cstdlib>

using namespace std;
//para manejar los argumentos
Pcp* parseArgs(int argc, char* argv[]);

//Pcp::Pcp(){}

void Pcp::inicializarHilos(){
	for(int i=0; i<nHilos; ++i){
		Hilo h = Hilo(i);
		h.ejecutar();
		hilos[i] = &h;
	}
}

int Pcp::hiloDisponible(){
	for (int i=0; i<nHilos; ++i){
		if(hilos[i]->getDisponible())
			return i;
	}
	return -1;
}

int Pcp::hiloTerminado(){
	for(int i=0; i<nHilos; ++i){
		if(hilos[i]->getTerminado())
			return i;
	}
	return -1;
}

void Pcp::procesarMensaje(){
	int hiloT = hiloTerminado();
	while(hiloT > -1){
		Estadistica e = hilos[hiloT]->genEstadistica(this->getId());
		Mensaje* m = this->getMensaje();
		m->estadisticas[hilos[hiloT]->getTareaId()] = e;
		this->setMensaje(m);
		hilos[hiloT]->setDisponible();
		hiloT = hiloTerminado();
	}
	int hiloId = hiloDisponible();
	if(hiloId<0) return;
	for(int i=0; i<(*(this->getMensaje())).nTareas and hiloId>-1; ++i){
		if(!((this->getMensaje())->tareas[i].asignado)){
			hilos[hiloId]->asignarTarea((this->getMensaje())->tareas[i], i);
		}
		hiloId = hiloDisponible();
	}
}

void Pcp::setValues(int id, int nHilos){
	this->id = id;
	this->nHilos = nHilos;
	pthread_t hilos[nHilos];
}

int Pcp::getId(){
	return this->id;
}

int Pcp::getNHilos(){
	return this->nHilos;
}

int main(int argc, char* argv[]){
	Pcp* me = parseArgs(argc, argv);
//	cerr << "Tengo " << me->getNHilos() << " hilos.\n";
	me->inicializarHilos();
	Mensaje m;
	read(0, &m, sizeof(Mensaje));
	me->setMensaje(&m);
	while(!me->esHoraDeTerminar()){
//		cerr << "Todavia no es hora de terminar\n";
		me->procesarMensaje();
		write(1, me->getMensaje(), sizeof(Mensaje));
		Mensaje m;
		read(0, &m, sizeof(Mensaje));
	}
//	cerr << "El PLP# " << me->getId() << " ha terminado" << endl;
//	me->printMessagetoErr(); 
	return 0;
}

Pcp* parseArgs(int argc, char*argv[]){
	/* Se recibe el argumento para determinar
	 * el numero de hilos que se van a usar
	 */
	extern char* optarg;
	extern int optind, opterr, optopt;
	int option, id=-1, hilos;
	Pcp* me = new Pcp();
	while((option = getopt(argc, argv, "i:t:"))!=-1){
		switch(option){
			case 'i':
				id = atoi(optarg);
				break;
			case 't':
				hilos = atoi(optarg);
				break;
		}
	}
	if(id < 0){
		cerr << "ERROR. Se debe asignar un id al proceso" << endl;
		exit(1);
	}
	me->setValues(id,hilos);
	return me;	
}

