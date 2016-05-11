#include "proceso.h"
#include <pthread.h>

class Pcp : Proceso{
 private:
  int id;
  int nHilos;
  pthread_t hilos[];
 public:
  Pcp(int id, int nHilos);
  ~Pcp();
  void asignarTarea(int nHilo, Tarea* t);
  void verificarEstadoHilos(); //determina si ya terminaron las tareas de cada hilo
};
