#include "proceso.h"
#include "hilo.h"
#include <pthread.h>

#define MAX_THREADS 19

class Pcp : public Proceso{
	private:
		int id;
		int nHilos;
		Hilo* hilos[MAX_THREADS];
	public:
		void setValues(int id, int nHilos);
		int getId();
		int getNHilos();
		void procesarMensaje();
		void inicializarHilos();
		int hiloTerminado();
		int hiloDisponible();
		void setDisponible();
};
