#include <sys/types.h> //best practices 4 fork
#include <unistd.h> //getopt, fork, pipe, dup, etc.
#include <iostream> //entrada y salida estandar
#include <map> //para el manejo de hilos y procesos
#include <cstdlib> //para el atoi

pid_t fork(void); //para mejor documentacion: pid_t 
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
      cout << "Asignando numero de procesos\n";
      pcps = atoi(optarg); //convierte char* en int
      n_is_used = true;
      for (int i=0; i<pcps; ++i) threadspcp[i] = 3;
      break;
    case 't': // para cuando asignen los hijos
      //se controla que se haya usado el -n previamente
      if(n_is_used){
	cout << "Asignando " << argv[optind] << " hilos al proceso " << optarg << endl;
	ts = atoi(argv[optind]);
	ns = atoi(optarg);
	threadspcp[ns] = ts;
      }else{
	cout << "No se ha asignado el numero de procesos\n" <<
	  "Use -n para asignar el numero de procesos\n";
      }
      break;
    default: //en caso de que no se ingrese una opcion valida
      cout << "No se reconoce la opcion ingresada. Utilice -n para asignar el numero de procesos, y Utilice -t para asignar el numero de hilos a cada proceso." << endl;
      break;
    }
  }
  /*
   * Si no se pasan argumentos, el valor por defecto
   * para ambos casos es de 3
   */
  if (pcps < 0){
    cout << "Asignando numero de procesos por defecto (3) \n";
    pcps = 3;
    cout << "Asignando hilos a cada proceso por defecto (3) \n";
    for (int i=0; i<3; ++i) threadspcp[i] = 3;
  }

  /*
   * Ahora, empezamos a crear el anillo.
   * Primero se crea un proceso de tipo plp
   * el cual siempre debe ser creado.
   */
  pid_t plp;
  if( (plp = fork()) < 0 ){ //se hace el proceso hijo
    cerr << "Ocurrio un error al crear el nuevo proceso\n";
  }else if (plp == 0){//proceso creado
    //aqui se hace un exec para el plp
  }else{ //proceso principal
    for(int i=0; i<pcps; ++i){ //hacer fork per proceso
      // ¿...?
    }
  }
}
