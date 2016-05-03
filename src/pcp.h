#include "proceso.h"
#include <pthread.h>

class Pcp : Proceso{
		private:
				const int DEFAULT_THREADS = 3;
				int id;
				int nHilos;
				pthread_t hilos[nHilos];
		public:
				Pcp(int id, int nHilos);
				Pcp(int id);
				~Pcp();
				asignarTarea(int nHilo, Tarea* t);
				verificarEstadoHilos(); //determina si ya terminaron las tareas de cada hilo
}
