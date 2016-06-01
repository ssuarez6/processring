#include <pthread.h>
#include <semaphore.h>
#include "mensaje.h"
class Hilo{
private:
	bool terminado = false;
	bool disponible = true;
	pthread_t h;
	sem_t *mutex;
	Tarea t;
	int tarea_id, id;
	char* rutaATarea;
public:
	Hilo(int id);
	void reset();
	void suicidar();
	void asignarTarea(Tarea t, int id_tarea);
//	void* ejecutarTarea(void*);
	void ejecutar(char* rutaATarea);
	Estadistica genEstadistica(int procesoID);
	int getTareaId();
	void setDisponible();
	sem_t* getMutex();
	void setTareaId(int t);
	void setTerminado(bool t);
	Tarea* getTarea();
};
