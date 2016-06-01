#include <sys/types.h> //best practices 4 fork
#include <unistd.h> //getopt, fork, pipe, dup, etc.
#include <iostream> //entrada y salida estandar
#include <map> //para el manejo de hilos y procesos
#include <cstdlib> //para el atoi
#include <cstdio>

#define IN 0
#define OUT 1

pid_t fork(void); //para mejor documentacion: pid_t

typedef int Tub[2];

using namespace std;


int main(int argc, char** argv){
	/* Primero, se hace el setup de las opciones que se tienen
	 * por linea de comandos. -n para asignar los procesos.
	 * -t asigna el numero de hilos a cada proceso.
	 * */
	extern char* optarg;
	extern int optind, opterr, optopt;
	int option, ts, ns;
	int pcps = -1;
	bool n_is_used = false;
	map<int, int> threadspcp;
	while((option = getopt(argc, argv, "n:t:")) != -1){
		switch(option){
			case 'n':
				pcps = atoi(optarg); //convierte char* en int
				n_is_used = true;
				for (int i=1; i<=pcps; ++i) threadspcp[i] = 3;
				break;
			case 't': // para cuando asignen los hijos
				//se controla que se haya usado el -n previamente
				if(n_is_used){
					ts = atoi(argv[optind]);
					ns = atoi(optarg);
					//el numero de hilos no puede ser mayor a 10
					if (ns > 10){
						exit(1);
					}
					threadspcp[ns] = ts;
				}else{
					cout << "No se ha asignado el numero de procesos\n" <<
						"Use -n para asignar el numero de procesos\n";
				}
				break;
			default: //en caso de que no se ingrese una opcion valida
				cout << "No se reconoce la opcion ingresada. Utilice -n para " <<
								"asignar el numero de procesos, y Utilice -t para asignari" <<
								" el numero de hilos a cada proceso." << endl;
				break;
		}
	}
	/*
	 * Si no se pasan argumentos, el valor por defecto
	 * para ambos casos es de 3
	 */
	if (pcps < 0){
		pcps = 3;
		for (int i=0; i<3; ++i) threadspcp[i] = 3;
	}

	/*
	 * Ahora, empezamos a crear el anillo.
	 * Primero se crea un proceso de tipo plp
	 */
	pid_t plp;
	Tub tubs[pcps+1]; //tuberias como pcps hayan
	for(int i=0; i<=pcps; ++i) pipe(tubs[i]); //inicializar pipes
	if ((plp=fork()) == 0){//proceso creado
		//aqui se hace un exec para el plp
		dup2(tubs[0][OUT], STDOUT_FILENO);
		dup2(tubs[pcps][IN], STDIN_FILENO);
		execl("./plp", "plp", NULL);
		for(int i=0; i<=pcps; ++i) {
			close(tubs[i][0]);
			close(tubs[i][1]);
		}//cerrando pipes
	}else{ //planificador
		for(int i=1; i<=pcps; ++i){ //hacer fork por proceso
			pid_t pcp;
			if ((pcp=fork()) == 0){   //"hijo"
				dup2(tubs[i][OUT], STDOUT_FILENO); //dups
				dup2(tubs[i-1][IN], STDIN_FILENO);
				for(int j=0;j<pcps;++j){
					close(tubs[j][0]);
					close(tubs[j][1]);
				} //cerrar tubs
				char is[2], ts[2];
				sprintf(is, "%d", i);
				sprintf(ts, "%d", threadspcp[i]);
				if(execl("./pcp", "pcp", "-i", is, "-t", ts, NULL ) == -1){
					cout << "ERROR en el exec" << endl;
					break;
				}
			}else{
				//dup2(tub[1], STDERR_FILENO);
				//close(tub[0]); close(tub[1]);
			}
		}
	}
}
