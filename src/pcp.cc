#include <iostream> //entrada y salida
#include <unistd.h>
#include "pcp.h"
#include <cstdlib>

using namespace std;

//constructor
Pcp::Pcp(int id, int nHilos): id(id), nHilos(nHilos){
	pthread_t hilos [nHilos];
}

//destructor
Pcp::~Pcp(){}

void Pcp::asignarTarea(int nHilo, Tarea* t){
	//asignar la tarea al hilo lalalala
}

void Pcp::verificarEstadoHilos(){
	//verificar el estado de los hilos lalalala
}

void Proceso::procesarMensaje(){
	//proceso el mensaje lalalala
}

int main(int argc, char* argv[]){
	/* Se recibe el argumento para determinar
	* el numero de hilos que se van a usar
	*/

	extern char* optarg;
	extern int optind, opterr, optopt;
	int option, id=-1, hilos;
	Pcp* me;
	cerr << "Antes del while\n";
	while((option = getopt(argc, argv, "i:t:"))!=-1){
		switch(option){
			case 'i':
			cerr << "Asignando id al pcp." << endl;
			id = atoi(optarg);
			break;
			case 't':
			cerr << "Asignando threads al pcp" << endl;
			hilos = atoi(optarg);
			break;
		}
	}
	if(id < 0){
		cerr << "ERROR. Se debe asignar un id al proceso" << endl;
		exit(1);
	}
	me = new Pcp(id, hilos);
}
