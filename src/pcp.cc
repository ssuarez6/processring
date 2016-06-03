#include <iostream> //entrada y salida
#include <unistd.h>
#include "pcp.h"
#include <cstdlib>

using namespace std;
//para manejar los argumentos

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
			cerr << "El hilo " << i << " ha terminado" << endl;
			return i;
	}
	return -1;
}

void Pcp::procesarMensaje(){
	imprimirEstadoHilos();
	int hiloId = hiloDisponible();
	Mensaje m = *(this->getMensaje());
	if(hiloId<0) return;
	for(int i=0; i<m.nTareas and hiloId>-1; ++i){
		cerr << "Hilo disponible: " << hiloId << endl;
		if(!(m.tareas[i].asignado)){
			cerr << "La tarea " << i << "no tiene asignacion" << endl;
			hilos[hiloId]->asignarTarea(m.tareas[i], i);
			m.tareas[i].asignado = true;
			m.tareas[i].procesoId = id;
			m.tareas[i].hiloId = hiloId;
			cerr << "Asigne " << m.tareas[i].tareaAEjecutar <<
				" al hilo " << hiloId;
		}
		hiloId = hiloDisponible();
		cerr << "Proximo hilo: " << hiloId << endl;
	}

	int hiloT = hiloTerminado();
	while(hiloT > -1){
		Estadistica e = hilos[hiloT]->genEstadistica(this->getId());
		Mensaje* m = this->getMensaje();
		int eId = hilos[hiloT]->getTareaId();
		m->estadisticas[eId] = e;
		this->setMensaje(m);
		hilos[hiloT]->setDisponible();
		hiloT = hiloTerminado();
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

void Pcp::matarHilos(){
	for(int i=0; i<nHilos; ++i)
		hilos[i]->suicidar();
}

void Pcp::imprimirEstadoHilos(){
	for(int i=0; i<nHilos; ++i){
		cerr << "Hilo #" << hilos[i]->getId()
		<< endl << "Terminado? " << hilos[i]->getTerminado()
		<< endl << "Disponible? " << hilos[i]->getDisponible()
		<< endl << "Tarea a ejecutar: " << hilos[i]->getTarea()->tareaAEjecutar
		<< endl;
	}
}

int main(int argc, char* argv[]){
	Pcp* me = parseArgs(argc, argv);
	me->inicializarHilos();
	me->leerMensaje();
	//me->printMessagetoErr();
	//me->imprimirEstadoHilos();
	while(!me->esHoraDeTerminar()){
		me->procesarMensaje();
		cerr << "procesé el mensaje" << endl;
		me->imprimirMensaje();
		cerr << "imprimi el mensaje" << endl;
		me->leerMensaje();
		cerr << "lei una vez" << endl;
		//me->printMessagetoErr();
	}
	cerr << "El PCP#" << me->getId() << " ha terminado su ejecución\n";
	cerr << "Matando hilos: " << endl;
	me->matarHilos();
	return 0;
}
