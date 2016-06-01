#include <iostream> //entrada y salida
#include <unistd.h>
#include "pcp.h"
#include <cstdlib>

using namespace std;
//para manejar los argumentos
Pcp* parseArgs(int argc, char* argv[]);

void Pcp::inicializarHilos(){
	for(int i=0; i<nHilos; ++i){
		Hilo h = *(new Hilo(i));
		h.ejecutar("algun path");
		hilos[i] = h;
	}
}

void Pcp::procesarMensaje(){
	int hiloT = hiloTerminado();
	while(hiloT > -1){
		Estadistica e = hilos[hiloT].genEstadistica(this->getId());
		Mensaje* m = this->getMensaje();
		m->estadisticas[hilos[hiloT].getTareaId()] = e;
		this->setMensaje(m);
		hilos[hiloT].setDisponible();
		hiloT = hiloTerminado();
	}
	int hiloId = hiloDisponible();
	if(hiloId<0) return;
	for(int i=0; i<(*(this->getMensaje())).nTareas and hiloId>-1; ++i){
		if(!((this->getMensaje())->tareas[i].asignado)){
			hilos[hiloId].asignarTarea((this->getMensaje())->tareas[i], i);
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
	Mensaje m;
	read(0, &m, sizeof(Mensaje));
	me->setMensaje(&m);
	me->printMessagetoErr(); 
	return 0;
}

Pcp* parseArgs(int argc, char*argv[]){
	/* Se recibe el argumento para determinar
	 * el numero de hilos que se van a usar
	 */
	extern char* optarg;
	extern int optind, opterr, optopt;
	int option, id=-1, hilos;
	Pcp* me;
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
	me = new Pcp();
	me->setValues(id,hilos);
	return me;	
}

