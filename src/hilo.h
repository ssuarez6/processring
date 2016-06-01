#include <pthread.h>
#include <semaphore.h>
#include "mensaje.h"
class Hilo{
private:
	bool terminado = false;
	bool disponible = true;
	pthread_t h;
	Tarea t;
	int tarea_id, id;
public:
	Hilo(int id);
	sem_t mutex;
	void reset();
	void suicidar();
	void asignarTarea(Tarea t, int id_tarea);
//	void* ejecutarTarea(void*);
	void ejecutar();
	Estadistica genEstadistica(int procesoID);
	int getTareaId();
	void setDisponible();
	void setTareaId(int t);
	void setTerminado(bool t);
	bool getDisponible();
	bool getTerminado();
	Tarea* getTarea();
};
