#include <unistd.h>
#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;
int main(int argc, char** argv){
  extern char* optarg;
  extern int optind, opterr, optopt;
  int option;
  int pcps = -1;
  map<int, int> threadspcp;
  while((option = getopt(argc, argv, "n:t:")) != -1){
    switch(option){
    case 'n':
      cout << "Asignando numero de procesadores\n";
      pcps = atoi(optarg);
      for (int i=0; i<pcps; ++i)
	threadspcp[i] = 3;
      break;
    case 't':
      cout << "Asignando " << argv[optind] << " hilos al proceso " << optarg << endl;
      int ts = atoi(argv[optind]);
      int ns = atoi(optarg);
      threadspcp[ns] = ts;
      break;
    default:
      cout << "No se han asignado procesos ni hilos por defecto. Valor por defecto: 3\n";
      pcps = 3;
      threadspcp[0] = 3;
      threadspcp[1] = 3;
      threadspcp[2] = 3;
      break;
    }
  }
}
